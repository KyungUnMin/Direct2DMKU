#pragma once
#include "BossFSMBase.h"

enum class NoiseStateType
{
	//Movement
	Idle,
	Slide,
	Defeat,
	Taunt,
	JumpToStage,
	Sing,
	JumpToField,

	//Attack
	AxeGrind,
	GuitarSlash,
	GuitarSlashDash,
	AxeDash,
	


	//Damaged
	NormalDamaged_Face,
	NormalDamaged_Stomach,
	NormalDamaged_Jaw,
	Damaged_BlowBack,
	Damaged_KnockDown,


	COUNT
};



class NoiseFSM : public BossFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	NoiseFSM();
	~NoiseFSM() override;

	NoiseFSM(const NoiseFSM& _Other) = delete;
	NoiseFSM(NoiseFSM&& _Other) noexcept = delete;
	NoiseFSM& operator=(const NoiseFSM& _Other) = delete;
	NoiseFSM& operator=(const NoiseFSM&& _Other) noexcept = delete;

	size_t GetRandomAttack() override;

	size_t GetRandomFarAttack() override;
	
	void Init(class FieldEnemyBase* _Enemy) override;



protected:

private:
	//근거리
	static const std::vector<std::vector<NoiseStateType>> NearAttackGroup;
	//원거리
	static const std::vector<std::vector<NoiseStateType>> FarAttackGroup;

};

