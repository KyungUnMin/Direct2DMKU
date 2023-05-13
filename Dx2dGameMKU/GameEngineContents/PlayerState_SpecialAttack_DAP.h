#pragma once
#include "PlayerStateBase.h"

class PlayerState_SpecialAttack_DAP : public PlayerStateBase
{
public:
	PlayerState_SpecialAttack_DAP();
	~PlayerState_SpecialAttack_DAP() override;

	PlayerState_SpecialAttack_DAP(const PlayerState_SpecialAttack_DAP& _Other) = delete;
	PlayerState_SpecialAttack_DAP(PlayerState_SpecialAttack_DAP&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_DAP& operator=(const PlayerState_SpecialAttack_DAP& _Other) = delete;
	PlayerState_SpecialAttack_DAP& operator=(const PlayerState_SpecialAttack_DAP&& _Other) noexcept = delete;

protected:

private:

};

