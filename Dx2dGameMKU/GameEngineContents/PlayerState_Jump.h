#pragma once
#include "PlayerState_MovementBase.h"

class PlayerState_Jump : public PlayerState_MovementBase
{
public:
	static const float MaxHeight;

	PlayerState_Jump();
	~PlayerState_Jump() override;

	PlayerState_Jump(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump(PlayerState_Jump&& _Other) noexcept = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump& _Other) = delete;
	PlayerState_Jump& operator=(const PlayerState_Jump&& _Other) noexcept = delete;

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
	

	void LoadAnimation();
	void CreateAnimation();
};

