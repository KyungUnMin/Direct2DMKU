#pragma once
#include "EnemyFSMBase.h"

enum class SchoolBoyStateType
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

class SchoolBoyFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	SchoolBoyFSM();
	~SchoolBoyFSM() override;

	SchoolBoyFSM(const SchoolBoyFSM& _Other) = delete;
	SchoolBoyFSM(SchoolBoyFSM&& _Other) noexcept = delete;
	SchoolBoyFSM& operator=(const SchoolBoyFSM& _Other) = delete;
	SchoolBoyFSM& operator=(const SchoolBoyFSM&& _Other) noexcept = delete;

	static SchoolBoyStateType GetRandomAttack();
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<SchoolBoyStateType> AttackGroup;



};

