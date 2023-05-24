#pragma once
#include "EnemyState_AttackBase.h"

class SchoolGirlState_Attack_CrescentKick : public EnemyState_AttackBase
{
public:
	SchoolGirlState_Attack_CrescentKick();
	~SchoolGirlState_Attack_CrescentKick() override;

	SchoolGirlState_Attack_CrescentKick(const SchoolGirlState_Attack_CrescentKick& _Other) = delete;
	SchoolGirlState_Attack_CrescentKick(SchoolGirlState_Attack_CrescentKick&& _Other) noexcept = delete;
	SchoolGirlState_Attack_CrescentKick& operator=(const SchoolGirlState_Attack_CrescentKick& _Other) = delete;
	SchoolGirlState_Attack_CrescentKick& operator=(const SchoolGirlState_Attack_CrescentKick&& _Other) noexcept = delete;

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
	static const float Duration;
	static const float4 ColOffset;
	static const float4 ColSize;

	int AttackCount = 0;
	float4 EnemyDir = float4::Zero;

	void LoadAnimation();
	void CreateAnimation();
};

