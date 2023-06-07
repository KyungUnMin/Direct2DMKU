#pragma once
#include "EnemyFSMBase.h"

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

	void SetMaxHp(int _MaxHp);
	
	void CalPhase(int _CurHp);

	inline bool IsLastPhase() const
	{
		return CurPhase == (AttackGroup.size() - 1);
	}

protected:

private:
	static const std::vector<std::vector<MisuzuStateType>> AttackGroup;

	size_t CurPhase = 0;
	size_t PhaseDivicer = 0;
	size_t MaxHp = 0;
};

