#pragma once
#include "EnemyFSMBase.h"

enum class HooliganStateType
{
	//Movement
	Idle,
	Walk,
	Ready,

	//Attack
	AxeKick,
	Elbow,
	Punch,
	SideKick,

	//Damaged
	NormalDamaged_Face,
	NormalDamaged_Stomach,
	NormalDamaged_Jaw,
	Damaged_BlowBack,
	Damaged_KnockDown,
	Damaged_WallHit,
	Damaged_WallOut,
	Damaged_Dazed,


	COUNT
};

class HooliganFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	HooliganFSM();
	~HooliganFSM() override;

	HooliganFSM(const HooliganFSM& _Other) = delete;
	HooliganFSM(HooliganFSM&& _Other) noexcept = delete;
	HooliganFSM& operator=(const HooliganFSM& _Other) = delete;
	HooliganFSM& operator=(const HooliganFSM&& _Other) noexcept = delete;

	size_t GetRandomAttack() override;
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<HooliganStateType> AttackGroup;



};

