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
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFolderName;
	static const float AniInterTime;

	const float StartGravity = 30.f;
	const float GravityAcc = 50.f;
	float NowGravity = 10.f;

	void LoadAnimation();
	void CreateAnimation();
};

