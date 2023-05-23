#pragma once
#include "EnemyState_AttackBase.h"

class TigerManState_Attack_Punch : public EnemyState_AttackBase
{
public:
	TigerManState_Attack_Punch();
	~TigerManState_Attack_Punch() override;

	TigerManState_Attack_Punch(const TigerManState_Attack_Punch& _Other) = delete;
	TigerManState_Attack_Punch(TigerManState_Attack_Punch&& _Other) noexcept = delete;
	TigerManState_Attack_Punch& operator=(const TigerManState_Attack_Punch& _Other) = delete;
	TigerManState_Attack_Punch& operator=(const TigerManState_Attack_Punch&& _Other) noexcept = delete;

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

