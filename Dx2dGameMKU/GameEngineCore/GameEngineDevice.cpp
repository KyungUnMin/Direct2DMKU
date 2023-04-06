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
	//��ǻ���� GPU�鿡 ���� ������ �˾ƿü� �ִ� �ڵ鷯
	IDXGIFactory* Factory = nullptr;

	//GPU�� ������ ������ ���� Com��ü�ڵ鷯(����̹��� ����ڸ� ��������ִ� �������̽�)
	IDXGIAdapter* Adapter = nullptr;

	//���丮 ����
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return;
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
			if (nullptr == Adapter)
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


	//��Ƽ���ϸ���� ����Ƽ 1¥���� �ִ�ġ�� �ִ´�
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;

	//TODO
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

	//DirectX���� ���� HDC �����
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
