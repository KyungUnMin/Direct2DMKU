#pragma once
#include "EnemyState_AttackBase.h"

class CheerleaderState_Attack_Punch : public EnemyState_AttackBase
{
public:
	CheerleaderState_Attack_Punch();
	~CheerleaderState_Attack_Punch() override;

	CheerleaderState_Attack_Punch(const CheerleaderState_Attack_Punch& _Other) = delete;
	CheerleaderState_Attack_Punch(CheerleaderState_Attack_Punch&& _Other) noexcept = delete;
	CheerleaderState_Attack_Punch& operator=(const CheerleaderState_Attack_Punch& _Other) = delete;
	CheerleaderState_Attack_Punch& operator=(const CheerleaderState_Attack_Punch&& _Other) noexcept = delete;

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

