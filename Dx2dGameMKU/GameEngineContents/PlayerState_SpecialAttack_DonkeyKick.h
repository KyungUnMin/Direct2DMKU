#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_SpecialAttack_DonkeyKick : public PlayerState_AttackBase
{
public:
	PlayerState_SpecialAttack_DonkeyKick();
	~PlayerState_SpecialAttack_DonkeyKick() override;

	PlayerState_SpecialAttack_DonkeyKick(const PlayerState_SpecialAttack_DonkeyKick& _Other) = delete;
	PlayerState_SpecialAttack_DonkeyKick(PlayerState_SpecialAttack_DonkeyKick&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_DonkeyKick& operator=(const PlayerState_SpecialAttack_DonkeyKick& _Other) = delete;
	PlayerState_SpecialAttack_DonkeyKick& operator=(const PlayerState_SpecialAttack_DonkeyKick&& _Other) noexcept = delete;

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

	int TotalDamage = 0;

	void LoadAnimation();
	void CreateAnimation();
};

