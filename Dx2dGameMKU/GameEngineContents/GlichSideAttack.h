#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GlichSideAttack : public GameEngineActor
{
public:
	GlichSideAttack();
	~GlichSideAttack() override;

	GlichSideAttack(const GlichSideAttack& _Other) = delete;
	GlichSideAttack(GlichSideAttack&& _Other) noexcept = delete;
	GlichSideAttack& operator=(const GlichSideAttack& _Other) = delete;
	GlichSideAttack& operator=(const GlichSideAttack&& _Other) noexcept = delete;

	inline void WaveOff(float _DecreseDuration = 1.f)
	{
		WaveOffValue = true;
		DecreseDuration = _DecreseDuration;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct GlichData
	{
		float Timer = 0.f;
		float Speed = 10.f;
		float Count = 30.f;
		float WaveDiff = 0.3f;

		float MaxWaveHeight = 1.f;
		float GlichRatio = 0.5f;
		float Garbage2;
		float Garbage3;
	};

	GlichData Data;

	bool WaveOffValue = false;
	float DecreseDuration = 0.f;
	float DecreaseTimer = 0.f;
};

