#pragma once
#include "PlayerStateBase.h"

class PlayerState_Dash : public PlayerStateBase
{
public:
	PlayerState_Dash();
	~PlayerState_Dash() override;

	PlayerState_Dash(const PlayerState_Dash& _Other) = delete;
	PlayerState_Dash(PlayerState_Dash&& _Other) noexcept = delete;
	PlayerState_Dash& operator=(const PlayerState_Dash& _Other) = delete;
	PlayerState_Dash& operator=(const PlayerState_Dash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFolderName;
	static const float AniInterTime;

	const float4 DashSpeed = float4{ 800.f, 400.f };

	void LoadAnimation();
	void CreateAnimation();
};

