#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_QickAttack_Chop : public PlayerState_AttackBase
{
public:
	PlayerState_QickAttack_Chop();
	~PlayerState_QickAttack_Chop() override;

	PlayerState_QickAttack_Chop(const PlayerState_QickAttack_Chop& _Other) = delete;
	PlayerState_QickAttack_Chop(PlayerState_QickAttack_Chop&& _Other) noexcept = delete;
	PlayerState_QickAttack_Chop& operator=(const PlayerState_QickAttack_Chop& _Other) = delete;
	PlayerState_QickAttack_Chop& operator=(const PlayerState_QickAttack_Chop&& _Other) noexcept = delete;

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

