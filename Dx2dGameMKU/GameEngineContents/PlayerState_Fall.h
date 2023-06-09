#pragma once
#include "PlayerState_MovementBase.h"


class PlayerState_Fall : public PlayerState_MovementBase
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
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	class PlayerFSM* FsmPtr = nullptr;
	const float Duration = 0.3f;
	float EnterHeight = 0.f;

	//이전에 움직임이 대시였는지 걷기였는지
	size_t PrevMoveState = -1;

	void LoadAnimation();
	void CreateAnimation();
};

