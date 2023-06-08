#pragma once
#include "BossFSMBase.h"

enum class MisuzuStateType
{
	//Movement
	Idle,
	Walk,
	Defeat,
	Taunt,

	//Attack
	GetUpAttack,
	Elbow,
	WUPunch,
	Tackle,
	Slap,
	Meteor,
	Roar,


	//Damaged
	NormalDamaged_Face,
	NormalDamaged_Stomach,
	NormalDamaged_Jaw,
	Damaged_BlowBack,
	Damaged_KnockDown,
	Damaged_Dizzy,
	Damaged_GroundHit,


	COUNT
};



class MisuzuFSM : public BossFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	MisuzuFSM();
	~MisuzuFSM() override;

	MisuzuFSM(const MisuzuFSM& _Other) = delete;
	MisuzuFSM(MisuzuFSM&& _Other) noexcept = delete;
	MisuzuFSM& operator=(const MisuzuFSM& _Other) = delete;
	MisuzuFSM& operator=(const MisuzuFSM&& _Other) noexcept = delete;

	size_t GetRandomAttack() override;

	size_t GetRandomFarAttack() override;
	
	void Init(class FieldEnemyBase* _Enemy) override;



protected:

private:
	//근거리
	static const std::vector<std::vector<MisuzuStateType>> NearAttackGroup;
	//원거리
	static const std::vector<std::vector<MisuzuStateType>> FarAttackGroup;

};

