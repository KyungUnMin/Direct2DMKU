#include "PrecompileHeader.h"
#include "GameEngineSampler.h"

GameEngineSampler::GameEngineSampler()
{

}

GameEngineSampler::~GameEngineSampler()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}


void GameEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Desc)
{
	//ReSetting할때 이미 샘플러를 만들었다면 다시 제거
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}

	Desc = _Desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&Desc, &State))\
	{
		MsgAssert("샘플러 생성에 실패했습니다" + GetNameToString());
	}
}

void GameEngineSampler::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetSamplers(_Slot, 1, &State);
}

void GameEngineSampler::PSSetting(UINT _Slot) 
{
	GameEngineDevice::GetContext()->PSSetSamplers(_Slot, 1, &State);
}