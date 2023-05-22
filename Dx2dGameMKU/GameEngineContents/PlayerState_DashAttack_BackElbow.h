#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_DashAttack_BackElbow : public PlayerState_AttackBase
{
public:
	PlayerState_DashAttack_BackElbow();
	~PlayerState_DashAttack_BackElbow() override;

	PlayerState_DashAttack_BackElbow(const PlayerState_DashAttack_BackElbow& _Other) = delete;
	PlayerState_DashAttack_BackElbow(PlayerState_DashAttack_BackElbow&& _Other) noexcept = delete;
	PlayerState_DashAttack_BackElbow& operator=(const PlayerState_DashAttack_BackElbow& _Other) = delete;
	PlayerState_DashAttack_BackElbow& operator=(const PlayerState_DashAttack_BackElbow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack(class FieldEnemyBase* _Enemy) override;


private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;
	static const float IneriaDuration;

	int TotalDamage = 0;

	void LoadAnimation();
	void CreateAnimation();
};

