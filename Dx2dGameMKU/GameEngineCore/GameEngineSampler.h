#pragma once
#include "GameEngineResource.h"

/*
�ؽ�ó�� �޽��� ��� �����ұ� ��� ��Ģ�� ���÷���� �Ѵ�(���� �����ϴ� ����, �ɼ�)
		UVW �� ���� XYZ�� �ǹ��Ѵ�
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
			MsgAssert("�������� �ʴ� ���÷��� �ɼ��� �����Ϸ��� �߽��ϴ�.");
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

