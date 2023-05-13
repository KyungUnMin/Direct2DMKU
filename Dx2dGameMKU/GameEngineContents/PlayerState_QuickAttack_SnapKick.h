#pragma once
#include "PlayerStateBase.h"

class PlayerState_QuickAttack_SnapKick : public PlayerStateBase
{
public:
	PlayerState_QuickAttack_SnapKick();
	~PlayerState_QuickAttack_SnapKick() override;

	PlayerState_QuickAttack_SnapKick(const PlayerState_QuickAttack_SnapKick& _Other) = delete;
	PlayerState_QuickAttack_SnapKick(PlayerState_QuickAttack_SnapKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_SnapKick& operator=(const PlayerState_QuickAttack_SnapKick& _Other) = delete;
	PlayerState_QuickAttack_SnapKick& operator=(const PlayerState_QuickAttack_SnapKick&& _Other) noexcept = delete;

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

