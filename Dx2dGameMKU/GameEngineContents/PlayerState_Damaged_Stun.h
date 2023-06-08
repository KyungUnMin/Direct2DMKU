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

private:
	static const std::string_view AniName;
	
	const float Duration = 1.5f;

	void LoadAnimation();
	void CreateAnimation();
};

