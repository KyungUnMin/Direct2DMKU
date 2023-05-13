#pragma once
#include "PlayerStateBase.h"

class PlayerState_UniqueAttack_HyrricaneKick : public PlayerStateBase
{
public:
	PlayerState_UniqueAttack_HyrricaneKick();
	~PlayerState_UniqueAttack_HyrricaneKick() override;

	PlayerState_UniqueAttack_HyrricaneKick(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick(PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;

protected:

private:

};

