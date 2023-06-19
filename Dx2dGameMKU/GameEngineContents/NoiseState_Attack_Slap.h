#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_Slap : public BossState_AttackBase
{
public:
	NoiseState_Attack_Slap();
	~NoiseState_Attack_Slap() override;

	NoiseState_Attack_Slap(const NoiseState_Attack_Slap& _Other) = delete;
	NoiseState_Attack_Slap(NoiseState_Attack_Slap&& _Other) noexcept = delete;
	NoiseState_Attack_Slap& operator=(const NoiseState_Attack_Slap& _Other) = delete;
	NoiseState_Attack_Slap& operator=(const NoiseState_Attack_Slap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;


	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;
	static const int AttackFrm;


	void LoadAnimation();
	void CreateAnimation();
};

