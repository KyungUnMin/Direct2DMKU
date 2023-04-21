#pragma once
#include "PlayerStateBase.h"


class PlayerStateMove : public PlayerStateBase
{
public:
	PlayerStateMove();
	~PlayerStateMove() override;

	PlayerStateMove(const PlayerStateMove& _Other) = delete;
	PlayerStateMove(PlayerStateMove&& _Other) noexcept = delete;
	PlayerStateMove& operator=(const PlayerStateMove& _Other) = delete;
	PlayerStateMove& operator=(const PlayerStateMove&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

