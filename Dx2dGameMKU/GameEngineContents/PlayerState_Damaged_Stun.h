#pragma once
#include "PlayerState_DamagedBase.h"

class PlayerState_Damaged_Stun : public PlayerState_DamagedBase
{
public:
	PlayerState_Damaged_Stun();
	~PlayerState_Damaged_Stun() override;

	PlayerState_Damaged_Stun(const PlayerState_Damaged_Stun& _Other) = delete;
	PlayerState_Damaged_Stun(PlayerState_Damaged_Stun&& _Other) noexcept = delete;
	PlayerState_Damaged_Stun& operator=(const PlayerState_Damaged_Stun& _Other) = delete;
	PlayerState_Damaged_Stun& operator=(const PlayerState_Damaged_Stun&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const std::string_view AniFileName;
	static const std::string_view EnterAniName;
	static const std::string_view LoopAniName;
	
	const float Duration = 1.5f;

	enum class State
	{
		Enter,
		Loop
	};

	State CurState = State::Enter;


	void LoadAnimation();
	void CreateAnimation();

	void Update_Enter();
	void Update_Loop();
};

