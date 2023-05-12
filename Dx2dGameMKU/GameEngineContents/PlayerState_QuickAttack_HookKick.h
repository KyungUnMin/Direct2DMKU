#pragma once
#include "PlayerStateBase.h"

class PlayerState_QuickAttack_HookKick : public PlayerStateBase
{
public:
	PlayerState_QuickAttack_HookKick();
	~PlayerState_QuickAttack_HookKick() override;

	PlayerState_QuickAttack_HookKick(const PlayerState_QuickAttack_HookKick& _Other) = delete;
	PlayerState_QuickAttack_HookKick(PlayerState_QuickAttack_HookKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_HookKick& operator=(const PlayerState_QuickAttack_HookKick& _Other) = delete;
	PlayerState_QuickAttack_HookKick& operator=(const PlayerState_QuickAttack_HookKick&& _Other) noexcept = delete;

protected:

private:

};

