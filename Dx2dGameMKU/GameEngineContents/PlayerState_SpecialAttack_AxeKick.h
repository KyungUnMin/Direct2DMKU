#pragma once
#include "PlayerStateBase.h"

class PlayerState_SpecialAttack_AxeKick : public PlayerStateBase
{
public:
	PlayerState_SpecialAttack_AxeKick();
	~PlayerState_SpecialAttack_AxeKick() override;

	PlayerState_SpecialAttack_AxeKick(const PlayerState_SpecialAttack_AxeKick& _Other) = delete;
	PlayerState_SpecialAttack_AxeKick(PlayerState_SpecialAttack_AxeKick&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_AxeKick& operator=(const PlayerState_SpecialAttack_AxeKick& _Other) = delete;
	PlayerState_SpecialAttack_AxeKick& operator=(const PlayerState_SpecialAttack_AxeKick&& _Other) noexcept = delete;

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

	void LoadAnimation();
	void CreateAnimation();
};

