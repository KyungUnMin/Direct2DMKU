#pragma once
#include "EnemyState_AttackBase.h"

class WaverState_Attack_DoubleSlash : public EnemyState_AttackBase
{
public:
	WaverState_Attack_DoubleSlash();
	~WaverState_Attack_DoubleSlash() override;

	WaverState_Attack_DoubleSlash(const WaverState_Attack_DoubleSlash& _Other) = delete;
	WaverState_Attack_DoubleSlash(WaverState_Attack_DoubleSlash&& _Other) noexcept = delete;
	WaverState_Attack_DoubleSlash& operator=(const WaverState_Attack_DoubleSlash& _Other) = delete;
	WaverState_Attack_DoubleSlash& operator=(const WaverState_Attack_DoubleSlash&& _Other) noexcept = delete;


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

	const float JumpDuration = 0.5f;
	const float JumpMaxHeight = 100.f;

	void LoadAnimation();
	void CreateAnimation();
};

