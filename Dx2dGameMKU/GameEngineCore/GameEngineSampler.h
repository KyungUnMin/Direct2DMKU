#pragma once
#include "GameEngineResource.h"

/*
텍스처를 메쉬에 어떻게 매핑할까 라는 규칙을 샘플러라고 한다(색상 결정하는 공식, 옵션)
		UVW 는 각각 XYZ를 의미한다
*/

class GameEngineSampler : public GameEngineResource<GameEngineSampler>
{
	friend class GameEngineSamplerSetter;

public:
	GameEngineSampler();
	~GameEngineSampler() override;

	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(const GameEngineSampler&& _Other) noexcept = delete;


	static std::shared_ptr<GameEngineSampler> Create(const std::string_view& _Name, const D3D11_SAMPLER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineSampler> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	static std::shared_ptr<GameEngineSampler> ReSetting(const std::string_view& _Name, const D3D11_SAMPLER_DESC& Desc)
	{
		std::shared_ptr<GameEngineSampler> NewSampler = GameEngineResource::Find(_Name);
		if (nullptr == NewSampler)
		{
			MsgAssert("존재하지 않는 샘플러의 옵션을 변경하려고 했습니다.");
			return nullptr;
		}

		NewSampler->ResCreate(Desc);
		return NewSampler;
	}

protected:

private:
	ID3D11SamplerState* State = nullptr;
	D3D11_SAMPLER_DESC Desc = D3D11_SAMPLER_DESC();

	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

