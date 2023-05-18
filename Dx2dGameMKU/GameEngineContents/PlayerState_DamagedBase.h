#pragma once
#include "PlayerStateBase.h"

class PlayerState_DamagedBase : public PlayerStateBase
{
public:
	PlayerState_DamagedBase();
	~PlayerState_DamagedBase() override;

	PlayerState_DamagedBase(const PlayerState_DamagedBase& _Other) = delete;
	PlayerState_DamagedBase(PlayerState_DamagedBase&& _Other) noexcept = delete;
	PlayerState_DamagedBase& operator=(const PlayerState_DamagedBase& _Other) = delete;
	PlayerState_DamagedBase& operator=(const PlayerState_DamagedBase&& _Other) noexcept = delete;

protected:

private:

};

