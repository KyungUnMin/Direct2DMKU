#pragma once
#include "EnemyFSMBase.h"

enum class SchoolGirlStateType
{
	//Movement
	Idle,
	Walk,
	Ready,

	//Attack
	CrescentKick,
	Jab,
	JumpKneeKick,
	Kick,

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

class SchoolGirlFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	SchoolGirlFSM();
	~SchoolGirlFSM() override;

	SchoolGirlFSM(const SchoolGirlFSM& _Other) = delete;
	SchoolGirlFSM(SchoolGirlFSM&& _Other) noexcept = delete;
	SchoolGirlFSM& operator=(const SchoolGirlFSM& _Other) = delete;
	SchoolGirlFSM& operator=(const SchoolGirlFSM&& _Other) noexcept = delete;

	static SchoolGirlStateType GetRandomAttack();
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<SchoolGirlStateType> AttackGroup;



};

