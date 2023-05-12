#pragma once
#include "PlayerStateBase.h"

class PlayerState_QuickAttack_SnapKick : public PlayerStateBase
{
public:
	PlayerState_QuickAttack_SnapKick();
	~PlayerState_QuickAttack_SnapKick() override;

	PlayerState_QuickAttack_SnapKick(const PlayerState_QuickAttack_SnapKick& _Other) = delete;
	PlayerState_QuickAttack_SnapKick(PlayerState_QuickAttack_SnapKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_SnapKick& operator=(const PlayerState_QuickAttack_SnapKick& _Other) = delete;
	PlayerState_QuickAttack_SnapKick& operator=(const PlayerState_QuickAttack_SnapKick&& _Other) noexcept = delete;

protected:

private:

};

