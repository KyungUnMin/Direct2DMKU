#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_DashAttack_DropKick : public PlayerState_AttackBase
{
public:
	PlayerState_DashAttack_DropKick();
	~PlayerState_DashAttack_DropKick() override;

	PlayerState_DashAttack_DropKick(const PlayerState_DashAttack_DropKick& _Other) = delete;
	PlayerState_DashAttack_DropKick(PlayerState_DashAttack_DropKick&& _Other) noexcept = delete;
	PlayerState_DashAttack_DropKick& operator=(const PlayerState_DashAttack_DropKick& _Other) = delete;
	PlayerState_DashAttack_DropKick& operator=(const PlayerState_DashAttack_DropKick&& _Other) noexcept = delete;

protected:
	void Attack(class FieldEnemyBase* _Enemy) override
	{

	}

private:

};

