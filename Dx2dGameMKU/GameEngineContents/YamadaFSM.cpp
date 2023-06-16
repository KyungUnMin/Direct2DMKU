#include "PrecompileHeader.h"
#include "YamadaFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "YamadaState_Idle.h"
#include "YamadaState_Walk.h"
#include "YamadaState_Defeat.h"
#include "YamadaState_Taunt.h"
#include "YamadaState_TeleportDisappear.h"
#include "YamadaState_TeleportAppear.h"
#include "YamadaState_PhaseTransition.h"

//Attack
#include "YamadaState_Attack_Blast.h"
#include "YamadaState_Attack_ForceField.h"
#include "YamadaState_Attack_QuickCombo.h"
#include "YamadaState_Attack_MatterCrush.h"
#include "YamadaState_Attack_Wormchi.h"

//Damaged
#include "YamadaState_NormalDamaged_Face.h"
#include "YamadaState_NormalDamaged_Stomach.h"
#include "YamadaState_NormalDamaged_Jaw.h"
#include "YamadaState_Damaged_BlowBack.h"
#include "YamadaState_Damaged_KnockDown.h"


const  std::string_view YamadaFSM::NormalDamaged_FileName = "Yamada_GetHit.png";

//근거리
const std::vector<std::vector<YamadaStateType>> YamadaFSM::NearAttackGroup =
{
	//1페이즈
	{
		YamadaStateType::QuickCombo,
	},

	//2페이즈
	{
		YamadaStateType::QuickCombo,
		YamadaStateType::TeleportDisappear,
	},

	//3페이즈
	{
		YamadaStateType::QuickCombo,
		YamadaStateType::Blast,
		YamadaStateType::TeleportDisappear,
	},
};

//원거리
const std::vector<std::vector<YamadaStateType>> YamadaFSM::FarAttackGroup =
{
	//1페이즈
	{
		YamadaStateType::Wormchi,
		YamadaStateType::MatterCrush,
	},

	//2페이즈
	{
		YamadaStateType::ForceField,
		YamadaStateType::MatterCrush,
	},

	//3페이즈
	{
		YamadaStateType::ForceField,
		YamadaStateType::MatterCrush,
		YamadaStateType::Wormchi,
	},
};


size_t YamadaFSM::GetRandomAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(NearAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(NearAttackGroup[CurPhase][RandValue]);
}

size_t YamadaFSM::GetRandomFarAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();

	//해당 페이즈에 원거리 공격이 존재하지 않는경우
	if (true == FarAttackGroup[CurPhase].empty())
		return -1;

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FarAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(FarAttackGroup[CurPhase][RandValue]);
}



YamadaFSM::YamadaFSM()
{

}

YamadaFSM::~YamadaFSM()
{

}



void YamadaFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(YamadaStateType::COUNT);


	//Movement
	FSMBase::CreateState<YamadaState_Idle>(YamadaStateType::Idle);
	FSMBase::CreateState<YamadaState_Walk>(YamadaStateType::Walk);
	FSMBase::CreateState<YamadaState_Defeat>(YamadaStateType::Defeat);
	FSMBase::CreateState<YamadaState_Taunt>(YamadaStateType::Taunt);
	FSMBase::CreateState<YamadaState_TeleportDisappear>(YamadaStateType::TeleportDisappear);
	FSMBase::CreateState<YamadaState_TeleportAppear>(YamadaStateType::TeleportAppear);
	FSMBase::CreateState<YamadaState_PhaseTransition>(YamadaStateType::PhaseTransition);


	//Attack
	FSMBase::CreateState<YamadaState_Attack_Blast>(YamadaStateType::Blast);
	FSMBase::CreateState<YamadaState_Attack_ForceField>(YamadaStateType::ForceField);
	FSMBase::CreateState<YamadaState_Attack_QuickCombo>(YamadaStateType::QuickCombo);
	FSMBase::CreateState<YamadaState_Attack_MatterCrush>(YamadaStateType::MatterCrush);
	FSMBase::CreateState<YamadaState_Attack_Wormchi>(YamadaStateType::Wormchi);


	//Damaged
	FSMBase::CreateState<YamadaState_NormalDamaged_Face>(YamadaStateType::NormalDamaged_Face);
	FSMBase::CreateState<YamadaState_NormalDamaged_Stomach>(YamadaStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<YamadaState_NormalDamaged_Jaw>(YamadaStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<YamadaState_Damaged_BlowBack>(YamadaStateType::Damaged_BlowBack);
	FSMBase::CreateState<YamadaState_Damaged_KnockDown>(YamadaStateType::Damaged_KnockDown);




	FSMBase::ChangeState(YamadaStateType::Idle);
}


