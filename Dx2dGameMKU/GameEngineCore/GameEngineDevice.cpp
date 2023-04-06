#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;



GameEngineDevice::GameEngineDevice()
{

}

GameEngineDevice::~GameEngineDevice()
{

}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdater()
{
	//컴퓨터의 GPU들에 대한 정보를 알아올수 있는 핸들러
	IDXGIFactory* Factory = nullptr;

	//GPU의 정보를 얻어오기 위한 Com객체핸들러(드라이버와 사용자를 연결시켜주는 인터페이스)
	IDXGIAdapter* Adapter = nullptr;

	//팩토리 생성
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return;
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
			if (nullptr == Adapter)
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


	//안티에일리어싱 퀄리티 1짜리를 최대치로 넣는다
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;

	//TODO
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

	//DirectX계의 메인 HDC 만들기
	CreateSwapChain();
}



void GameEngineDevice::Release()
{
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
