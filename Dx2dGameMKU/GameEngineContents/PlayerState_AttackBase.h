#pragma once
#include "PlayerStateBase.h"

class PlayerState_AttackBase : public PlayerStateBase
{
public:
	PlayerState_AttackBase();
	~PlayerState_AttackBase() override;

	PlayerState_AttackBase(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase(PlayerState_AttackBase&& _Other) noexcept = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void ExitState() override;

private:

};

