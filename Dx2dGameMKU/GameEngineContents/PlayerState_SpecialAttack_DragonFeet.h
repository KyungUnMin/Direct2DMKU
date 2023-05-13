#pragma once
#include "PlayerStateBase.h"

class PlayerState_SpecialAttack_DragonFeet : public PlayerStateBase
{
public:
	PlayerState_SpecialAttack_DragonFeet();
	~PlayerState_SpecialAttack_DragonFeet() override;

	PlayerState_SpecialAttack_DragonFeet(const PlayerState_SpecialAttack_DragonFeet& _Other) = delete;
	PlayerState_SpecialAttack_DragonFeet(PlayerState_SpecialAttack_DragonFeet&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_DragonFeet& operator=(const PlayerState_SpecialAttack_DragonFeet& _Other) = delete;
	PlayerState_SpecialAttack_DragonFeet& operator=(const PlayerState_SpecialAttack_DragonFeet&& _Other) noexcept = delete;

protected:

private:

};

