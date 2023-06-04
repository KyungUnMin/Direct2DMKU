#pragma once
#include "EnemyFSMBase.h"

enum class MisuzuStateType
{
	//Movement
	Idle,
	Walk,

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
	Damaged_Dizzy,


	COUNT
};

class MisuzuFSM : public EnemyFSMBase
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
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<MisuzuStateType> AttackGroup;



};

