#pragma once
#include "BossState_IdleBase.h"

class NoiseState_Idle : public BossState_IdleBase
{
public:
	NoiseState_Idle();
	~NoiseState_Idle() override;

	NoiseState_Idle(const NoiseState_Idle& _Other) = delete;
	NoiseState_Idle(NoiseState_Idle&& _Other) noexcept = delete;
	NoiseState_Idle& operator=(const NoiseState_Idle& _Other) = delete;
	NoiseState_Idle& operator=(const NoiseState_Idle&& _Other) noexcept = delete;

	static const std::vector<int> FarAttackPercent;
	static const float SightRadius;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;



	void LoadAnimation();
	void CreateAnimation();

};

