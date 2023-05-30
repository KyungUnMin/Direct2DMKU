#pragma once
#include "EnemyState_AttackBase.h"

class WaverState_Attack_DiceSpike : public EnemyState_AttackBase
{
public:
	WaverState_Attack_DiceSpike();
	~WaverState_Attack_DiceSpike() override;

	WaverState_Attack_DiceSpike(const WaverState_Attack_DiceSpike& _Other) = delete;
	WaverState_Attack_DiceSpike(WaverState_Attack_DiceSpike&& _Other) noexcept = delete;
	WaverState_Attack_DiceSpike& operator=(const WaverState_Attack_DiceSpike& _Other) = delete;
	WaverState_Attack_DiceSpike& operator=(const WaverState_Attack_DiceSpike&& _Other) noexcept = delete;

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

