#pragma once
#include "EnemyState_AttackBase.h"

class HooliganState_Attack_DodgeKick : public EnemyState_AttackBase
{
public:
	HooliganState_Attack_DodgeKick();
	~HooliganState_Attack_DodgeKick() override;

	HooliganState_Attack_DodgeKick(const HooliganState_Attack_DodgeKick& _Other) = delete;
	HooliganState_Attack_DodgeKick(HooliganState_Attack_DodgeKick&& _Other) noexcept = delete;
	HooliganState_Attack_DodgeKick& operator=(const HooliganState_Attack_DodgeKick& _Other) = delete;
	HooliganState_Attack_DodgeKick& operator=(const HooliganState_Attack_DodgeKick&& _Other) noexcept = delete;


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

	const float MaxBackAcc = 500.f;
	const float BackMoveDuration = AniInterTime * 5.f;
	float4 BackMoveDir = float4::Zero;


	void LoadAnimation();
	void CreateAnimation();
	void Update_BackMove(float _DeltaTime);
};

