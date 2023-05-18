#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_UniqueAttack_DragonFeet : public PlayerState_AttackBase
{
public:
	static const int NeedMp;
	
	PlayerState_UniqueAttack_DragonFeet();
	~PlayerState_UniqueAttack_DragonFeet() override;

	PlayerState_UniqueAttack_DragonFeet(const PlayerState_UniqueAttack_DragonFeet& _Other) = delete;
	PlayerState_UniqueAttack_DragonFeet(PlayerState_UniqueAttack_DragonFeet&& _Other) noexcept = delete;
	PlayerState_UniqueAttack_DragonFeet& operator=(const PlayerState_UniqueAttack_DragonFeet& _Other) = delete;
	PlayerState_UniqueAttack_DragonFeet& operator=(const PlayerState_UniqueAttack_DragonFeet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack(class FieldEnemyBase* _Enemy) override
	{
		int a = 0;
	}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	class FieldCamController* CamCtrl = nullptr;

	void LoadAnimation();
	void CreateAnimation();
};

