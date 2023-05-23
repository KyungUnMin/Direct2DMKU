#pragma once
#include "EnemyState_AttackBase.h"

class TigerManState_Attack_AxeKick : public EnemyState_AttackBase
{
public:
	TigerManState_Attack_AxeKick();
	~TigerManState_Attack_AxeKick() override;

	TigerManState_Attack_AxeKick(const TigerManState_Attack_AxeKick& _Other) = delete;
	TigerManState_Attack_AxeKick(TigerManState_Attack_AxeKick&& _Other) noexcept = delete;
	TigerManState_Attack_AxeKick& operator=(const TigerManState_Attack_AxeKick& _Other) = delete;
	TigerManState_Attack_AxeKick& operator=(const TigerManState_Attack_AxeKick&& _Other) noexcept = delete;

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

