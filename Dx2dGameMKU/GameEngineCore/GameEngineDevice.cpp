#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRenderTarget.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;
std::shared_ptr<GameEngineRenderTarget> GameEngineDevice::BackBufferTarget = nullptr;


GameEngineDevice::GameEngineDevice()
{

}

GameEngineDevice::~GameEngineDevice()
{

}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdater()
{
	//컴퓨터의 GPU들에 대한 정보를 알아올수 있는 핸들러
	//다렉에서는 오브젝트를 얻어오기 위해서는
	// 항상 팩토리를 통해서 얻을 수 있게끔 만들어져 있다
	IDXGIFactory* Factory = nullptr;

	//GPU의 정보를 얻어오기 위한 Com객체핸들러(드라이버와 사용자를 연결시켜주는 인터페이스)
	IDXGIAdapter* Adapter = nullptr;

	//팩토리 생성
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	//찾은 GPU들 중에 최대 메모리 크기
	size_t PrevAdapterVideoMemory = 0;

	for (UINT AdapterIndex = 0; ; ++AdapterIndex)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		//n번째 그래픽 카드의 어뎁터를 추출해옴, 없으면 nullptr
		Factory->EnumAdapters(AdapterIndex, &CurAdapter);
		if (nullptr == CurAdapter)
			break;

		//어뎁터의 정보가 기록되는 구조체
		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		//이전에 찾은 GPU의 메모리보다 큰 경우
		if (PrevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			PrevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			//이전 GPU와 연결된 어뎁터 반환
			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		//이전에 찾은 GPU의 메모리보다 작은 경우엔 생성한 이번에 어뎁터 반환
		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}



void GameEngineDevice::CreateSwapChain()
{
	//이미지의 버퍼 크기를 정하기 위한 스크린 사이즈
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//스왑체인(이미지 버퍼)의 정보를 기록하는 구조체
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };


	//더블버퍼링을 위해 2개 만든다
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();


	//화면 최소 프레임
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	//화면 최대 프레임
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;


	//그래픽 색상 모드
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//그래픽을 모니터에 출력할 방향
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//???
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//그래픽 모드 : 윈도우용 & 쉐이더 사용
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;


	//안티에일리어싱 Msaa 1짜리를 최대치로 넣는다(확실하지 않음)
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
	//???
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	//해상도 변경 가능 옵션이지만 변경할 일 없음
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//false일 시 전체화면
	SwapChainDesc.Windowed = true;


	//SwapChainDesc에 기록한 옵션들을 이용해 SwapChain을 만든다
	//SwapChain을 만들기 위해서는 앞서 만든 Device를 통해 Factory를 다시 만들어야 하는데,
	//Device를 만들때 Factory에 대한 정보도 존재한다
	IDXGIDevice* SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	
	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	//GetAdapter 함수를 호출하는것과 같다
	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	//GetFactory 함수를 호출하는것과 같다
	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	//스왑체인 생성
	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("스왑체인 생성에 실패했습니다.");
		return;
	}

	//스왑체인에 생성했으므로 위에서 사용했던 핸들러들은 삭제시킨다
	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	
	//스왑체인 내부에 있는 비트맵을 뽑아온다
	ID3D11Texture2D* SwapBackBufferTexture = nullptr;
	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&SwapBackBufferTexture));
	if (S_OK != Result)
	{
		MsgAssert("스왑체인의 텍스처를 가져오는데 실패했습니다");
		return;
	}

	//받아온 비트맵은 별도의 텍스처클래스에 저장하고
	std::shared_ptr<GameEngineTexture> BackBufferTexture = std::make_shared<GameEngineTexture>();
	BackBufferTexture->Create(SwapBackBufferTexture);

	//그 비트맵을 수정할수 있는 권한인 렌더타겟(DC)을 만들어 그 비트맵을 관리하게 한다.
	BackBufferTarget = GameEngineRenderTarget::Create("MainBackBufferTarget", BackBufferTexture, float4{ 0.f, 0.f, 1.f, 1.f });
}

void GameEngineDevice::RenderStart()
{
	BackBufferTarget->Clear();
}

void GameEngineDevice::RenderEnd() 
{
	//내부적으로 더블 버퍼링을 이용한다.
	//렌더링 하고 있는 렌더타켓이 아직 렌더링 중이라면 
	//여유분의 다른 렌더 타겟에 그리고
	//렌더링 하고 있던 렌더타겟이 끝났다면
	//대기중이였던 렌더타켓을 렌더링 시킨다
	HRESULT Result = SwapChain->Present(0, 0);

	//문제가 생기거나 해당도가 변경됐다면 조건문 안에 들어올 것이다.
	if(Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgAssert("렌더 타겟 생성에 실패하였습니다");
		return;
	}

}



void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetHWnd())
	{
		MsgAssert("윈도우가 만들어지지도 않았는데, 디바이스를 초기화 할 수는 없습니다");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif 

	//Direct11에 맞는 GPU 수준
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	//내가 가지고 있는 최고 성능의 GPU와 연결된 어뎁터 핸들러 가져오기
	IDXGIAdapter* Adapter = GetHighPerformanceAdater();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽 카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다");
		return;
	}

	//디바이스, 컨텍스트 만들기
	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		MsgAssert("디바이스 생성에 실패했습니다");
		return;
	}

	//어뎁터의 역할은 다 했으므로 Release
	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	
	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	//DX 안에서 멀티스레드 기능을 On
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	//DirectX계의 메인 HDC 만들기
	CreateSwapChain();
}



void GameEngineDevice::Release()
{
	BackBufferTarget = nullptr;

	if (nullptr == SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}
}
