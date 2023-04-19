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

	//받은 텍스처를 바탕으로 렌더타겟을 생성
	CreateRenderTargetView();
}

void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟을 만들 수는 없습니다.");
		return;
	}

	//디바이스를 이용해 텍스처에 따른 실제 렌더타겟을 만든다
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTarget);

	if (S_OK != Result)
	{
		MsgAssert("렌더타겟 생성에 실패하였습니다");
		return;
	}
}


void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
}