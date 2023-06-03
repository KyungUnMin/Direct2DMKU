#pragma once
#include "PlayerState_MovementBase.h"

class PlayerState_Dash : public PlayerState_MovementBase
{
public:
	static const float4 DashSpeed;

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
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
	void CreateEffect();
};

