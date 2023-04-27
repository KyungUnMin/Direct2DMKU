#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Release\\DirectXTex.lib")
#endif


GameEngineTexture::GameEngineTexture()
{

}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != DSV)
	{
		DSV->Release();
		DSV = nullptr;
	}
	
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}



void GameEngineTexture::ResCreate(ID3D11Texture2D* _Value)
{
	Texture2D = _Value;

	//���� ����ȭ�� �ؽ�ó�� ������ �޾ƿ´�
	Texture2D->GetDesc(&Desc);

	//���� �ؽ�ó�� �������� ����Ÿ���� ����
	CreateRenderTargetView();
}


void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴ� ����Ÿ�ٺ並 ���� ���� �����ϴ�.");
		return;
	}

	//����̽��� �̿��� �ؽ�ó�� ���� ���� ����Ÿ���� �����
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("����Ÿ�� �� ������ �����Ͽ����ϴ�");
		return;
	}
}



void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴµ� ���� ���ٽ� �並 ������� �����ϴ�");
		return;
	}

	HRESULT Result = GameEngineDevice::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);
	if (S_OK != Result)
	{
		MsgAssert("���� ���ٽ� �� ������ �����߽��ϴ�");
		return;
	}
}







void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
	GameEnginePath NewPath(_Path);

	//Ȯ����(�빮��)
	std::string Ext = GameEngineString::ToUpper(NewPath.GetExtension());
	
	//�����ڵ� Ǯ �н�
	std::wstring Path = GameEngineString::AnsiToUniCode(NewPath.GetFullPath());

	if (Ext == ".TGA")
	{
		MsgAssert("���� �ε��� �� ���� �����Դϴ�." + std::string(_Path.data()));
	}
	else if (Ext == ".DDS")
	{
		MsgAssert("���� �ε��� �� ���� �����Դϴ�." + std::string(_Path.data()));
	}

	//���ҽ� �ε�
	else if (S_OK != DirectX::LoadFromWICFile(Path.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
	}

	//�ε��� ���ҽ��� �������� SRV(���̴� ���ҽ� ��)�����
	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineDevice::GetDevice(),
		Image.GetImages(),			
		Image.GetImageCount(),	
		Image.GetMetadata(),			//���̳ʸ� �ڵ� ������
		&SRV
	))
	{
		MsgAssert("���̴� ���ҽ� �� ������ �����߽��ϴ�." + std::string(_Path.data()));
	}


	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height= static_cast<UINT>(Data.height);
}




void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}




void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Value)
{
	Desc = _Value;

	GameEngineDevice::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	//���� ���ۿ����� ���� �ؽ�ó���ٸ�
	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL == Desc.BindFlags)
	{
		CreateDepthStencilView();
	}

	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó ������ �����߽��ϴ�");
	}
}