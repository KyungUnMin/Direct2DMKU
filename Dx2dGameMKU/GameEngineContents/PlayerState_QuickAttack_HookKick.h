#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_QuickAttack_HookKick : public PlayerState_AttackBase
{
public:
	PlayerState_QuickAttack_HookKick();
	~PlayerState_QuickAttack_HookKick() override;

	PlayerState_QuickAttack_HookKick(const PlayerState_QuickAttack_HookKick& _Other) = delete;
	PlayerState_QuickAttack_HookKick(PlayerState_QuickAttack_HookKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_HookKick& operator=(const PlayerState_QuickAttack_HookKick& _Other) = delete;
	PlayerState_QuickAttack_HookKick& operator=(const PlayerState_QuickAttack_HookKick&& _Other) noexcept = delete;

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

