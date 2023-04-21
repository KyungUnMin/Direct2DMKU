#pragma once
#include "PlayerStateBase.h"

class PlayerState_Jump : public PlayerStateBase
{
public:
	PlayerState_Jump();
	~PlayerState_Jump() override;

	PlayerState_Jump(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump(PlayerState_Jump&& _Other) noexcept = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	const float JumpScale = 500.f;
	const float Duration = 0.5f;
	float LiveTime = 0.f;
	

};

