#pragma once
#include "PlayerState_MovementBase.h"

class PlayerState_BattleStart : public PlayerState_MovementBase
{
public:
	PlayerState_BattleStart();
	~PlayerState_BattleStart() override;

	PlayerState_BattleStart(const PlayerState_BattleStart& _Other) = delete;
	PlayerState_BattleStart(PlayerState_BattleStart&& _Other) noexcept = delete;
	PlayerState_BattleStart& operator=(const PlayerState_BattleStart& _Other) = delete;
	PlayerState_BattleStart& operator=(const PlayerState_BattleStart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const std::string_view AniFileName;
	static const std::string_view AniName_Fall;
	static const std::string_view AniName_Ready;


	std::shared_ptr<class GameEngineCollision> PlayerMainCollider = nullptr;
	enum class State
	{
		Fall,
		Ready,
	};

	State CurState = State::Fall;
	const float FallDuration = 0.5f;
	const float FallStartHeight = 1000.f;
	

	void LoadAnimation();
	void CreateAnimation();

	void Update_Fall(float _DeltaTime);
	void Update_Ready(float _DeltaTime);
};

