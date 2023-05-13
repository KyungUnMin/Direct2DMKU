#pragma once
#include "PlayerStateBase.h"

class PlayerState_QuickAttack_BackKick : public PlayerStateBase
{
public:
	PlayerState_QuickAttack_BackKick();
	~PlayerState_QuickAttack_BackKick() override;

	PlayerState_QuickAttack_BackKick(const PlayerState_QuickAttack_BackKick& _Other) = delete;
	PlayerState_QuickAttack_BackKick(PlayerState_QuickAttack_BackKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_BackKick& operator=(const PlayerState_QuickAttack_BackKick& _Other) = delete;
	PlayerState_QuickAttack_BackKick& operator=(const PlayerState_QuickAttack_BackKick&& _Other) noexcept = delete;

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

	bool IsReserveChainAttack = false;

	void LoadAnimation();
	void CreateAnimation();
};

