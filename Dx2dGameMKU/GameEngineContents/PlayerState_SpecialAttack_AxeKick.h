#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_SpecialAttack_AxeKick : public PlayerState_AttackBase
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

	void Attack(class FieldEnemyBase* _Enemy) override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	void LoadAnimation();
	void CreateAnimation();
};

