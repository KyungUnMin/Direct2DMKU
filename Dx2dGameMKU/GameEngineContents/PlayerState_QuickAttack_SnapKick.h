#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_QuickAttack_SnapKick : public PlayerState_AttackBase
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

	void Attack(class FieldEnemyBase* _Enemy) override
	{
		int a = 0;
	}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	bool IsReserveChainAttack = false;

	void LoadAnimation();
	void CreateAnimation();
};

