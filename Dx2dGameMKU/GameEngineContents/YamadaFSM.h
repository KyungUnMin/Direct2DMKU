#pragma once
#include "BossFSMBase.h"

enum class YamadaStateType
{
	//Movement
	Idle,
	Walk,
	Defeat,
	Taunt,
	TeleportDisappear,
	TeleportAppear,

	//Attack
	Blast,
	ForceField,
	QuickCombo,
	MatterCrush,

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



class YamadaFSM : public BossFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	YamadaFSM();
	~YamadaFSM() override;

	YamadaFSM(const YamadaFSM& _Other) = delete;
	YamadaFSM(YamadaFSM&& _Other) noexcept = delete;
	YamadaFSM& operator=(const YamadaFSM& _Other) = delete;
	YamadaFSM& operator=(const YamadaFSM&& _Other) noexcept = delete;

	size_t GetRandomAttack() override;

	size_t GetRandomFarAttack() override;
	
	void Init(class FieldEnemyBase* _Enemy) override;

protected:

private:
	//근거리
	static const std::vector<std::vector<YamadaStateType>> NearAttackGroup;
	//원거리
	static const std::vector<std::vector<YamadaStateType>> FarAttackGroup;

};

