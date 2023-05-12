#pragma once
#include "PlayerStateBase.h"

class PlayerState_QuickAttack_BackKick : public PlayerStateBase
{
public:
	PlayerState_QuickAttack_BackKick();
	~PlayerState_QuickAttack_BackKick() override;

	PlayerState_QuickAttack_BackKick(const PlayerState_QuickAttack_BackKick& _Other) = delete;
	PlayerState_QuickAttack_BackKick(PlayerState_QuickAttack_BackKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_BackKick& operator=(const PlayerState_QuickAttack_BackKick& _Other) = delete;
	PlayerState_QuickAttack_BackKick& operator=(const PlayerState_QuickAttack_BackKick&& _Other) noexcept = delete;

protected:

private:

};

