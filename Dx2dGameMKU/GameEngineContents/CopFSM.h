#pragma once
#include "EnemyFSMBase.h"

enum class CopStateType
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

class CopFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	CopFSM();
	~CopFSM() override;

	CopFSM(const CopFSM& _Other) = delete;
	CopFSM(CopFSM&& _Other) noexcept = delete;
	CopFSM& operator=(const CopFSM& _Other) = delete;
	CopFSM& operator=(const CopFSM&& _Other) noexcept = delete;

	static CopStateType GetRandomAttack();
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<CopStateType> AttackGroup;



};

