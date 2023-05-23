#pragma once
#include "EnemyState_AttackBase.h"

class SchoolGirlState_Attack_SideKick : public EnemyState_AttackBase
{
public:
	SchoolGirlState_Attack_SideKick();
	~SchoolGirlState_Attack_SideKick() override;

	SchoolGirlState_Attack_SideKick(const SchoolGirlState_Attack_SideKick& _Other) = delete;
	SchoolGirlState_Attack_SideKick(SchoolGirlState_Attack_SideKick&& _Other) noexcept = delete;
	SchoolGirlState_Attack_SideKick& operator=(const SchoolGirlState_Attack_SideKick& _Other) = delete;
	SchoolGirlState_Attack_SideKick& operator=(const SchoolGirlState_Attack_SideKick&& _Other) noexcept = delete;

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

