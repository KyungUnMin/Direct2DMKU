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
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFolderName;
	static const float AniInterTime;

	class PlayerFSM* FsmPtr = nullptr;
	const float Duration = 0.3f;
	const float MaxHeight = 300.f;
	

	void LoadAnimation();
	void CreateAnimation();
};

