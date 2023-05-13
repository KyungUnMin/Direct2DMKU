#pragma once
#include "PlayerStateBase.h"

class PlayerState_SpecialAttack_HyrricaneKick : public PlayerStateBase
{
public:
	PlayerState_SpecialAttack_HyrricaneKick();
	~PlayerState_SpecialAttack_HyrricaneKick() override;

	PlayerState_SpecialAttack_HyrricaneKick(const PlayerState_SpecialAttack_HyrricaneKick& _Other) = delete;
	PlayerState_SpecialAttack_HyrricaneKick(PlayerState_SpecialAttack_HyrricaneKick&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_HyrricaneKick& operator=(const PlayerState_SpecialAttack_HyrricaneKick& _Other) = delete;
	PlayerState_SpecialAttack_HyrricaneKick& operator=(const PlayerState_SpecialAttack_HyrricaneKick&& _Other) noexcept = delete;

protected:

private:

};

