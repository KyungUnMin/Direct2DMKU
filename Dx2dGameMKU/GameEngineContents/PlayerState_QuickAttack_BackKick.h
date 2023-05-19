#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_QuickAttack_BackKick : public PlayerState_AttackBase
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

	void Attack(class FieldEnemyBase* _Enemy) override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	bool IsReserveChainAttack = false;
	int TotalDamage = 0;

	void LoadAnimation();
	void CreateAnimation();
};

