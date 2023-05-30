#pragma once
#include "EnemyState_AttackBase.h"

class WaverState_Attack_Slash : public EnemyState_AttackBase
{
public:
	WaverState_Attack_Slash();
	~WaverState_Attack_Slash() override;

	WaverState_Attack_Slash(const WaverState_Attack_Slash& _Other) = delete;
	WaverState_Attack_Slash(WaverState_Attack_Slash&& _Other) noexcept = delete;
	WaverState_Attack_Slash& operator=(const WaverState_Attack_Slash& _Other) = delete;
	WaverState_Attack_Slash& operator=(const WaverState_Attack_Slash&& _Other) noexcept = delete;

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

