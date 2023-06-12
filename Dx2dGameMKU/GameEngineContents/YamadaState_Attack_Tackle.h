#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_Tackle : public BossState_AttackBase
{
public:
	YamadaState_Attack_Tackle();
	~YamadaState_Attack_Tackle() override;

	YamadaState_Attack_Tackle(const YamadaState_Attack_Tackle& _Other) = delete;
	YamadaState_Attack_Tackle(YamadaState_Attack_Tackle&& _Other) noexcept = delete;
	YamadaState_Attack_Tackle& operator=(const YamadaState_Attack_Tackle& _Other) = delete;
	YamadaState_Attack_Tackle& operator=(const YamadaState_Attack_Tackle&& _Other) noexcept = delete;

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

