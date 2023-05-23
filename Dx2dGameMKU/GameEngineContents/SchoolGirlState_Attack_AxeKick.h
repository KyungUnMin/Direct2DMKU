#pragma once
#include "EnemyState_AttackBase.h"

class SchoolGirlState_Attack_AxeKick : public EnemyState_AttackBase
{
public:
	SchoolGirlState_Attack_AxeKick();
	~SchoolGirlState_Attack_AxeKick() override;

	SchoolGirlState_Attack_AxeKick(const SchoolGirlState_Attack_AxeKick& _Other) = delete;
	SchoolGirlState_Attack_AxeKick(SchoolGirlState_Attack_AxeKick&& _Other) noexcept = delete;
	SchoolGirlState_Attack_AxeKick& operator=(const SchoolGirlState_Attack_AxeKick& _Other) = delete;
	SchoolGirlState_Attack_AxeKick& operator=(const SchoolGirlState_Attack_AxeKick&& _Other) noexcept = delete;

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

	void LoadAnimation();
	void CreateAnimation();
};

