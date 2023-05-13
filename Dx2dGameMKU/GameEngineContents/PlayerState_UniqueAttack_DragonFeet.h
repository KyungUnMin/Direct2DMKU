#pragma once
#include "PlayerStateBase.h"

class PlayerState_UniqueAttack_DragonFeet : public PlayerStateBase
{
public:
	PlayerState_UniqueAttack_DragonFeet();
	~PlayerState_UniqueAttack_DragonFeet() override;

	PlayerState_UniqueAttack_DragonFeet(const PlayerState_UniqueAttack_DragonFeet& _Other) = delete;
	PlayerState_UniqueAttack_DragonFeet(PlayerState_UniqueAttack_DragonFeet&& _Other) noexcept = delete;
	PlayerState_UniqueAttack_DragonFeet& operator=(const PlayerState_UniqueAttack_DragonFeet& _Other) = delete;
	PlayerState_UniqueAttack_DragonFeet& operator=(const PlayerState_UniqueAttack_DragonFeet&& _Other) noexcept = delete;

protected:

private:

};

