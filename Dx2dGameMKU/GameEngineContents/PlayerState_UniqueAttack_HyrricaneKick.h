#pragma once
#include "PlayerStateBase.h"

class PlayerState_UniqueAttack_HyrricaneKick : public PlayerStateBase
{
public:
	PlayerState_UniqueAttack_HyrricaneKick();
	~PlayerState_UniqueAttack_HyrricaneKick() override;

	PlayerState_UniqueAttack_HyrricaneKick(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick(PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;

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
};

