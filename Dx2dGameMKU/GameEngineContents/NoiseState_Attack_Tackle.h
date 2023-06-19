#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_Tackle : public BossState_AttackBase
{
public:
	NoiseState_Attack_Tackle();
	~NoiseState_Attack_Tackle() override;

	NoiseState_Attack_Tackle(const NoiseState_Attack_Tackle& _Other) = delete;
	NoiseState_Attack_Tackle(NoiseState_Attack_Tackle&& _Other) noexcept = delete;
	NoiseState_Attack_Tackle& operator=(const NoiseState_Attack_Tackle& _Other) = delete;
	NoiseState_Attack_Tackle& operator=(const NoiseState_Attack_Tackle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

private:
	static const std::string_view TackleStart_AniFileName;
	static const std::string_view TackleLoop_AniFileName;
	static const std::pair<int, int> TackleStart_AniCutFrame;
	static const std::pair<int, int> TackleLoop_AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	bool IsLaunched = false;

	float4 TackleDir = float4::Zero;
	const float MaxSpeed = 1500.f;
	const float TackleDuration = 1.5f;
	float LaunchTime = 0.f;
	

	void LoadAnimation();
	void CreateAnimation();

	bool TackleMove(float _DeltaTime);
	void CreateCollEffect();
};

