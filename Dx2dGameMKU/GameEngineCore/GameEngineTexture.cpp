#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture()
{

}

GameEngineTexture::~GameEngineTexture()
{
	if(nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}

	if (nullptr != RenderTarget)
	{
		RenderTarget->Release();
		RenderTarget = nullptr;
	}
}



void GameEngineTexture::ResCreate(ID3D11Texture2D* _Value)
{
	Texture2D = _Value;

	//���� �ؽ�ó�� �������� ����Ÿ���� ����
	CreateRenderTargetView();
}

void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴ� ����Ÿ���� ���� ���� �����ϴ�.");
		return;
	}

	//����̽��� �̿��� �ؽ�ó�� ���� ���� ����Ÿ���� �����
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTarget);

	if (S_OK != Result)
	{
		MsgAssert("����Ÿ�� ������ �����Ͽ����ϴ�");
		return;
	}
}


void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
}