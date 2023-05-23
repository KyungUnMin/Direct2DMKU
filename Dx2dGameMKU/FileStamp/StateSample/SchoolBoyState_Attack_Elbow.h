#pragma once
#include "EnemyState_AttackBase.h"

class SchoolBoyState_Attack_Elbow : public EnemyState_AttackBase
{
public:
	SchoolBoyState_Attack_Elbow();
	~SchoolBoyState_Attack_Elbow() override;

	SchoolBoyState_Attack_Elbow(const SchoolBoyState_Attack_Elbow& _Other) = delete;
	SchoolBoyState_Attack_Elbow(SchoolBoyState_Attack_Elbow&& _Other) noexcept = delete;
	SchoolBoyState_Attack_Elbow& operator=(const SchoolBoyState_Attack_Elbow& _Other) = delete;
	SchoolBoyState_Attack_Elbow& operator=(const SchoolBoyState_Attack_Elbow&& _Other) noexcept = delete;


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

