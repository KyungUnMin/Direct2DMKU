#include "PrecompileHeader.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{

}

GameEngineBlend::~GameEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgAssert("생성되지 않은 블렌더 스테이트 입니다.");
	}

	//팩터라는 것을 직접 넣어줄수도 있다고 함, 필요하면 만들 예정
	if (Desc.RenderTarget[0].SrcBlend == D3D11_BLEND_BLEND_FACTOR)
	{
		MsgAssert("아직 처리 하지 않는 블랜드 방식입니다 블랜드 필터 입력기능을 만들어 주세요.");
	}


	GameEngineDevice::GetContext()->OMSetBlendState(State, nullptr, Mask);
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Value)
{
	Desc = _Value;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(&Desc, &State))
	{
		MsgAssert("블랜드 스테이트 생성에 실패했습니다.");
	}
}
