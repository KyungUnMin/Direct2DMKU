#pragma once
#include "EnemyState_AttackBase.h"
#include <GameEnginePlatform/GameEngineSound.h>

class WaverState_Attack_WindSlash : public EnemyState_AttackBase
{
public:
	WaverState_Attack_WindSlash();
	~WaverState_Attack_WindSlash() override;

	WaverState_Attack_WindSlash(const WaverState_Attack_WindSlash& _Other) = delete;
	WaverState_Attack_WindSlash(WaverState_Attack_WindSlash&& _Other) noexcept = delete;
	WaverState_Attack_WindSlash& operator=(const WaverState_Attack_WindSlash& _Other) = delete;
	WaverState_Attack_WindSlash& operator=(const WaverState_Attack_WindSlash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

	void OnAttackSound() {}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	GameEngineSoundPlayer SfxPlayer;

	void LoadAnimation();
	void CreateAnimation();
};

