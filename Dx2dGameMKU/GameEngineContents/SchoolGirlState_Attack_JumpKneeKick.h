#pragma once
#include "EnemyState_AttackBase.h"

class SchoolGirlState_Attack_JumpKneeKick : public EnemyState_AttackBase
{
public:
	SchoolGirlState_Attack_JumpKneeKick();
	~SchoolGirlState_Attack_JumpKneeKick() override;

	SchoolGirlState_Attack_JumpKneeKick(const SchoolGirlState_Attack_JumpKneeKick& _Other) = delete;
	SchoolGirlState_Attack_JumpKneeKick(SchoolGirlState_Attack_JumpKneeKick&& _Other) noexcept = delete;
	SchoolGirlState_Attack_JumpKneeKick& operator=(const SchoolGirlState_Attack_JumpKneeKick& _Other) = delete;
	SchoolGirlState_Attack_JumpKneeKick& operator=(const SchoolGirlState_Attack_JumpKneeKick&& _Other) noexcept = delete;

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
	static const float Duration;

	void LoadAnimation();
	void CreateAnimation();
};

