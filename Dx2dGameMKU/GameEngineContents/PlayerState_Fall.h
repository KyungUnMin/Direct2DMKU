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

private:
	static const std::string_view AniName;
	static const std::string_view AniFolderName;
	static const float AniInterTime;

	const float Duration = 0.2f;
	float EnterHeight = 0.f;

	void LoadAnimation();
	void CreateAnimation();
};

