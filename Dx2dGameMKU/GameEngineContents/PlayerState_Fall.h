#pragma once
#include "PlayerStateBase.h"

class PlayerState_Fall : public PlayerStateBase
{
public:
	PlayerState_Fall();
	~PlayerState_Fall() override;

	PlayerState_Fall(const PlayerState_Fall& _Other) = delete;
	PlayerState_Fall(PlayerState_Fall&& _Other) noexcept = delete;
	PlayerState_Fall& operator=(const PlayerState_Fall& _Other) = delete;
	PlayerState_Fall& operator=(const PlayerState_Fall&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	const float StartGravity = 300.f;
	const float GravityAcc = 500.f;
	float NowGravity = 100.f;

};

