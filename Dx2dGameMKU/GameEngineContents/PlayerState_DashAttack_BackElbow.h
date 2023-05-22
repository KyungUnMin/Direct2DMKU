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
	void Attack(class FieldEnemyBase* _Enemy) override
	{

	}

private:

};

