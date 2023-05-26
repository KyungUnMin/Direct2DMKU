#pragma once
#include "EnemyState_AttackBase.h"


class TigerManState_Attack_Boot : public EnemyState_AttackBase
{
public:
	TigerManState_Attack_Boot();
	~TigerManState_Attack_Boot() override;

	TigerManState_Attack_Boot(const TigerManState_Attack_Boot& _Other) = delete;
	TigerManState_Attack_Boot(TigerManState_Attack_Boot&& _Other) noexcept = delete;
	TigerManState_Attack_Boot& operator=(const TigerManState_Attack_Boot& _Other) = delete;
	TigerManState_Attack_Boot& operator=(const TigerManState_Attack_Boot&& _Other) noexcept = delete;

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

