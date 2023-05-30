#pragma once
#include "EnemyState_AttackBase.h"

class WaverState_Attack_Kick : public EnemyState_AttackBase
{
public:
	WaverState_Attack_Kick();
	~WaverState_Attack_Kick() override;

	WaverState_Attack_Kick(const WaverState_Attack_Kick& _Other) = delete;
	WaverState_Attack_Kick(WaverState_Attack_Kick&& _Other) noexcept = delete;
	WaverState_Attack_Kick& operator=(const WaverState_Attack_Kick& _Other) = delete;
	WaverState_Attack_Kick& operator=(const WaverState_Attack_Kick&& _Other) noexcept = delete;

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

