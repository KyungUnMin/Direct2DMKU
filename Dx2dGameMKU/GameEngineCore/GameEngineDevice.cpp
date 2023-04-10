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
	//��ǻ���� GPU�鿡 ���� ������ �˾ƿü� �ִ� �ڵ鷯
	//�ٷ������� ������Ʈ�� ������ ���ؼ���
	// �׻� ���丮�� ���ؼ� ���� �� �ְԲ� ������� �ִ�
	IDXGIFactory* Factory = nullptr;

	//GPU�� ������ ������ ���� Com��ü�ڵ鷯(����̹��� ����ڸ� ��������ִ� �������̽�)
	IDXGIAdapter* Adapter = nullptr;

	//���丮 ����
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	//ã�� GPU�� �߿� �ִ� �޸� ũ��
	size_t PrevAdapterVideoMemory = 0;

	for (UINT AdapterIndex = 0; ; ++AdapterIndex)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		//n��° �׷��� ī���� ��͸� �����ؿ�, ������ nullptr
		Factory->EnumAdapters(AdapterIndex, &CurAdapter);
		if (nullptr == CurAdapter)
			break;

		//����� ������ ��ϵǴ� ����ü
		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		//������ ã�� GPU�� �޸𸮺��� ū ���
		if (PrevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			PrevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			//���� GPU�� ����� ��� ��ȯ
			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		//������ ã�� GPU�� �޸𸮺��� ���� ��쿣 ������ �̹��� ��� ��ȯ
		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}



void GameEngineDevice::CreateSwapChain()
{
	//�̹����� ���� ũ�⸦ ���ϱ� ���� ��ũ�� ������
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//����ü��(�̹��� ����)�� ������ ����ϴ� ����ü
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };


	//������۸��� ���� 2�� �����
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();


	//ȭ�� �ּ� ������
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	//ȭ�� �ִ� ������
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;


	//�׷��� ���� ���
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//�׷����� ����Ϳ� ����� ����
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//???
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//�׷��� ��� : ������� & ���̴� ���
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;


	//��Ƽ���ϸ���� Msaa 1¥���� �ִ�ġ�� �ִ´�(Ȯ������ ����)
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
	//???
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	//�ػ� ���� ���� �ɼ������� ������ �� ����
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//false�� �� ��üȭ��
	SwapChainDesc.Windowed = true;


	//SwapChainDesc�� ����� �ɼǵ��� �̿��� SwapChain�� �����
	//SwapChain�� ����� ���ؼ��� �ռ� ���� Device�� ���� Factory�� �ٽ� ������ �ϴµ�,
	//Device�� ���鶧 Factory�� ���� ������ �����Ѵ�
	IDXGIDevice* SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	
	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	//GetAdapter �Լ��� ȣ���ϴ°Ͱ� ����
	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	//GetFactory �Լ��� ȣ���ϴ°Ͱ� ����
	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	//����ü�� ����
	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("����ü�� ������ �����߽��ϴ�.");
		return;
	}

	//����ü�ο� ���������Ƿ� ������ ����ߴ� �ڵ鷯���� ������Ų��
	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	
	//����ü�� ���ο� �ִ� ��Ʈ���� �̾ƿ´�
	ID3D11Texture2D* SwapBackBufferTexture = nullptr;
	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&SwapBackBufferTexture));
	if (S_OK != Result)
	{
		MsgAssert("����ü���� �ؽ�ó�� �������µ� �����߽��ϴ�");
		return;
	}

	//�޾ƿ� ��Ʈ���� ������ �ؽ�óŬ������ �����ϰ�
	std::shared_ptr<GameEngineTexture> BackBufferTexture = std::make_shared<GameEngineTexture>();
	BackBufferTexture->Create(SwapBackBufferTexture);

	//�� ��Ʈ���� �����Ҽ� �ִ� ������ ����Ÿ��(DC)�� ����� �� ��Ʈ���� �����ϰ� �Ѵ�.
	BackBufferTarget = GameEngineRenderTarget::Create("MainBackBufferTarget", BackBufferTexture, float4{ 0.f, 0.f, 1.f, 1.f });
}

void GameEngineDevice::RenderStart()
{
	BackBufferTarget->Clear();
}

void GameEngineDevice::RenderEnd() 
{
	//���������� ���� ���۸��� �̿��Ѵ�.
	//������ �ϰ� �ִ� ����Ÿ���� ���� ������ ���̶�� 
	//�������� �ٸ� ���� Ÿ�ٿ� �׸���
	//������ �ϰ� �ִ� ����Ÿ���� �����ٸ�
	//������̿��� ����Ÿ���� ������ ��Ų��
	HRESULT Result = SwapChain->Present(0, 0);

	//������ ����ų� �ش絵�� ����ƴٸ� ���ǹ� �ȿ� ���� ���̴�.
	if(Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgAssert("���� Ÿ�� ������ �����Ͽ����ϴ�");
		return;
	}

}



void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetHWnd())
	{
		MsgAssert("�����찡 ����������� �ʾҴµ�, ����̽��� �ʱ�ȭ �� ���� �����ϴ�");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif 

	//Direct11�� �´� GPU ����
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	//���� ������ �ִ� �ְ� ������ GPU�� ����� ��� �ڵ鷯 ��������
	IDXGIAdapter* Adapter = GetHighPerformanceAdater();

	if (nullptr == Adapter)
	{
		MsgAssert("�׷��� ī�� ��ġ ��� �������̽��� �����µ� �����߽��ϴ�");
		return;
	}

	//����̽�, ���ؽ�Ʈ �����
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
		MsgAssert("����̽� ������ �����߽��ϴ�");
		return;
	}

	//����� ������ �� �����Ƿ� Release
	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	
	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("���̷�Ʈ 11�� �������� �ʴ� �׷���ī�� �Դϴ�");
		return;
	}

	//DX �ȿ��� ��Ƽ������ ����� On
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	//DirectX���� ���� HDC �����
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
