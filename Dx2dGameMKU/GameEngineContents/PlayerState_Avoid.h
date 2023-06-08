#pragma once
#include "PlayerState_MovementBase.h"

class PlayerState_Avoid : public PlayerState_MovementBase
{
public:
	PlayerState_Avoid();
	~PlayerState_Avoid();

	PlayerState_Avoid(const PlayerState_Avoid& _Other) = delete;
	PlayerState_Avoid(PlayerState_Avoid&& _Other) noexcept = delete;
	PlayerState_Avoid& operator=(const PlayerState_Avoid& _Other) = delete;
	PlayerState_Avoid& operator=(const PlayerState_Avoid&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const std::string_view AniName;

	static const float MaxSpeed;
	static const float MaxHeight;
	static const float Duration;

	float4 MoveDir = float4::Zero;
	
	void ImageLoad();
	void CreateAnimation();

	void CreateEffect();
	void Update_Move(float _DeltaTime, float _Ratio);
	void Update_Jump(float _Ratio);

};

