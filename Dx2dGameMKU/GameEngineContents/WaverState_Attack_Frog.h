#pragma once
#include "EnemyState_AttackBase.h"

class WaverState_Attack_Frog : public EnemyState_AttackBase
{
public:
	WaverState_Attack_Frog();
	~WaverState_Attack_Frog() override;

	WaverState_Attack_Frog(const WaverState_Attack_Frog& _Other) = delete;
	WaverState_Attack_Frog(WaverState_Attack_Frog&& _Other) noexcept = delete;
	WaverState_Attack_Frog& operator=(const WaverState_Attack_Frog& _Other) = delete;
	WaverState_Attack_Frog& operator=(const WaverState_Attack_Frog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	const float JumpDuration = AniInterTime * 5.f;
	const float JumpMaxHeight = 50.f;

	float JumpTimer = 0.0f;
	float LastAttackTime = 0.f;


	void LoadAnimation();
	void CreateAnimation();
};

