#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_QuickAttack_CrescentKick : public PlayerState_AttackBase
{
public:
	PlayerState_QuickAttack_CrescentKick();
	~PlayerState_QuickAttack_CrescentKick() override;

	PlayerState_QuickAttack_CrescentKick(const PlayerState_QuickAttack_CrescentKick& _Other) = delete;
	PlayerState_QuickAttack_CrescentKick(PlayerState_QuickAttack_CrescentKick&& _Other) noexcept = delete;
	PlayerState_QuickAttack_CrescentKick& operator=(const PlayerState_QuickAttack_CrescentKick& _Other) = delete;
	PlayerState_QuickAttack_CrescentKick& operator=(const PlayerState_QuickAttack_CrescentKick&& _Other) noexcept = delete;

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

