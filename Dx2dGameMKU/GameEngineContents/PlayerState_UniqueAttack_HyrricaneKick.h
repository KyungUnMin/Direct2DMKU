#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_UniqueAttack_HyrricaneKick : public PlayerState_AttackBase
{
public:
	static const int NeedMp;

	PlayerState_UniqueAttack_HyrricaneKick();
	~PlayerState_UniqueAttack_HyrricaneKick() override;

	PlayerState_UniqueAttack_HyrricaneKick(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick(PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick& _Other) = delete;
	PlayerState_UniqueAttack_HyrricaneKick& operator=(const PlayerState_UniqueAttack_HyrricaneKick&& _Other) noexcept = delete;

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

	class FieldCamController* CamCtrl = nullptr;
	bool IsHit = false;
	int TotalDamage = 0;

	void LoadAnimation();
	void CreateAnimation();
};

