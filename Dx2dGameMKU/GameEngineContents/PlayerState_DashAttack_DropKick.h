#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_DashAttack_DropKick : public PlayerState_AttackBase
{
public:
	PlayerState_DashAttack_DropKick();
	~PlayerState_DashAttack_DropKick() override;

	PlayerState_DashAttack_DropKick(const PlayerState_DashAttack_DropKick& _Other) = delete;
	PlayerState_DashAttack_DropKick(PlayerState_DashAttack_DropKick&& _Other) noexcept = delete;
	PlayerState_DashAttack_DropKick& operator=(const PlayerState_DashAttack_DropKick& _Other) = delete;
	PlayerState_DashAttack_DropKick& operator=(const PlayerState_DashAttack_DropKick&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack(class FieldEnemyBase* _Enemy) override;


private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;
	static const float IneriaDuration;

	int TotalDamage = 0;
	const float MaxHeight = 120.f;

	void LoadAnimation();
	void CreateAnimation();
};

