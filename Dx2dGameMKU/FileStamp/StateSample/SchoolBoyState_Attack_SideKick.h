#pragma once
#include "EnemyState_AttackBase.h"

class SchoolBoyState_Attack_SideKick : public EnemyState_AttackBase
{
public:
	SchoolBoyState_Attack_SideKick();
	~SchoolBoyState_Attack_SideKick() override;

	SchoolBoyState_Attack_SideKick(const SchoolBoyState_Attack_SideKick& _Other) = delete;
	SchoolBoyState_Attack_SideKick(SchoolBoyState_Attack_SideKick&& _Other) noexcept = delete;
	SchoolBoyState_Attack_SideKick& operator=(const SchoolBoyState_Attack_SideKick& _Other) = delete;
	SchoolBoyState_Attack_SideKick& operator=(const SchoolBoyState_Attack_SideKick&& _Other) noexcept = delete;

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

