#include "PrecompileHeader.h"
#include "NoiseFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "NoiseState_Idle.h"
#include "NoiseState_Slide.h"
#include "NoiseState_Defeat.h"
#include "NoiseState_Taunt.h"
#include "NoiseState_JumpToStage.h"
#include "NoiseState_Sing.h"
#include "NoiseState_JumpToField.h"

//Attack
#include "NoiseState_Attack_AxeGrind.h"
#include "NoiseState_Attack_GuitarSlash.h"
#include "NoiseState_Attack_GuitarSlashDash.h"
#include "NoiseState_Attack_AxeDash.h"

//Damaged
#include "NoiseState_NormalDamaged_Face.h"
#include "NoiseState_NormalDamaged_Stomach.h"
#include "NoiseState_NormalDamaged_Jaw.h"
#include "NoiseState_Damaged_BlowBack.h"
#include "NoiseState_Damaged_KnockDown.h"



const  std::string_view NoiseFSM::NormalDamaged_FileName = "Noise_GetHit.png";

//근거리
const std::vector<std::vector<NoiseStateType>> NoiseFSM::NearAttackGroup =
{
	//1페이즈
	{
		NoiseStateType::Slide,
		//NoiseStateType::Slap,
	},

	//2페이즈
	{
		NoiseStateType::GuitarSlash,
	},

	//3페이즈
	{
		NoiseStateType::AxeGrind,
	},
};

//원거리
const std::vector<std::vector<NoiseStateType>> NoiseFSM::FarAttackGroup =
{
	//1페이즈
	{
		NoiseStateType::Slide,
		NoiseStateType::GuitarSlashDash,
	},

	//2페이즈
	{
		NoiseStateType::Slide,
		NoiseStateType::GuitarSlashDash,
	},

	//3페이즈
	{
		NoiseStateType::AxeDash,
		NoiseStateType::GuitarSlashDash,
	},
};


size_t NoiseFSM::GetRandomAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(NearAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(NearAttackGroup[CurPhase][RandValue]);
}

size_t NoiseFSM::GetRandomFarAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();

	//해당 페이즈에 원거리 공격이 존재하지 않는경우
	if (true == FarAttackGroup[CurPhase].empty())
		return -1;

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FarAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(FarAttackGroup[CurPhase][RandValue]);
}



NoiseFSM::NoiseFSM()
{

}

NoiseFSM::~NoiseFSM()
{

}



void NoiseFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(NoiseStateType::COUNT);


	//Movement
	FSMBase::CreateState<NoiseState_Idle>(NoiseStateType::Idle);
	FSMBase::CreateState<NoiseState_Slide>(NoiseStateType::Slide);
	FSMBase::CreateState<NoiseState_Defeat>(NoiseStateType::Defeat);
	FSMBase::CreateState<NoiseState_Taunt>(NoiseStateType::Taunt);
	FSMBase::CreateState<NoiseState_JumpToStage>(NoiseStateType::JumpToStage);
	FSMBase::CreateState<NoiseState_Sing>(NoiseStateType::Sing);
	FSMBase::CreateState<NoiseState_JumpToField>(NoiseStateType::JumpToField);


	//Attack
	FSMBase::CreateState<NoiseState_Attack_AxeGrind>(NoiseStateType::AxeGrind);
	FSMBase::CreateState<NoiseState_Attack_GuitarSlash>(NoiseStateType::GuitarSlash);
	FSMBase::CreateState<NoiseState_Attack_GuitarSlashDash>(NoiseStateType::GuitarSlashDash);
	FSMBase::CreateState<NoiseState_Attack_AxeDash>(NoiseStateType::AxeDash);


	//Damaged
	FSMBase::CreateState<NoiseState_NormalDamaged_Face>(NoiseStateType::NormalDamaged_Face);
	FSMBase::CreateState<NoiseState_NormalDamaged_Stomach>(NoiseStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<NoiseState_NormalDamaged_Jaw>(NoiseStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<NoiseState_Damaged_BlowBack>(NoiseStateType::Damaged_BlowBack);
	FSMBase::CreateState<NoiseState_Damaged_KnockDown>(NoiseStateType::Damaged_KnockDown);


	FSMBase::ChangeState(NoiseStateType::Idle);
}

