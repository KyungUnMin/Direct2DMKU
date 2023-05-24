#include "PrecompileHeader.h"
#include "SchoolGirlFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "SchoolGirlState_Idle.h"
#include "SchoolGirlState_Walk.h"
#include "SchoolGirlState_Ready.h"

//Attack
#include "SchoolGirlState_Attack_CrescentKick.h"
#include "SchoolGirlState_Attack_Jab.h"
#include "SchoolGirlState_Attack_JumpKneeKick.h"
#include "SchoolGirlState_Attack_Kick.h"

//Damaged
#include "SchoolGirlState_NormalDamaged_Face.h"
#include "SchoolGirlState_NormalDamaged_Stomach.h"
#include "SchoolGirlState_NormalDamaged_Jaw.h"
#include "SchoolGirlState_Damaged_BlowBack.h"
#include "SchoolGirlState_Damaged_KnockDown.h"
#include "SchoolGirlState_Damaged_WallHit.h"
#include "SchoolGirlState_Damaged_WallOut.h"
#include "SchoolGirlState_Damaged_Dazed.h"


const  std::string_view SchoolGirlFSM::NormalDamaged_FileName = "SchoolGirl_GetHits.png";


const std::vector<SchoolGirlStateType> SchoolGirlFSM::AttackGroup =
{
	SchoolGirlStateType::CrescentKick,
	SchoolGirlStateType::Jab,
	SchoolGirlStateType::JumpKneeKick,
	SchoolGirlStateType::Kick
};

SchoolGirlStateType SchoolGirlFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return AttackGroup[RandValue];
}




SchoolGirlFSM::SchoolGirlFSM()
{

}

SchoolGirlFSM::~SchoolGirlFSM()
{

}



void SchoolGirlFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(SchoolGirlStateType::COUNT);


	//Movement
	FSMBase::CreateState<SchoolGirlState_Idle>(SchoolGirlStateType::Idle);
	FSMBase::CreateState<SchoolGirlState_Walk>(SchoolGirlStateType::Walk);
	FSMBase::CreateState<SchoolGirlState_Ready>(SchoolGirlStateType::Ready);


	//Attack
	FSMBase::CreateState<SchoolGirlState_Attack_CrescentKick>(SchoolGirlStateType::CrescentKick);
	FSMBase::CreateState<SchoolGirlState_Attack_Jab>(SchoolGirlStateType::Jab);
	FSMBase::CreateState<SchoolGirlState_Attack_JumpKneeKick>(SchoolGirlStateType::JumpKneeKick);
	FSMBase::CreateState<SchoolGirlState_Attack_Kick>(SchoolGirlStateType::Kick);


	//Damaged
	FSMBase::CreateState<SchoolGirlState_NormalDamaged_Face>(SchoolGirlStateType::NormalDamaged_Face);
	FSMBase::CreateState<SchoolGirlState_NormalDamaged_Stomach>(SchoolGirlStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<SchoolGirlState_NormalDamaged_Jaw>(SchoolGirlStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<SchoolGirlState_Damaged_BlowBack>(SchoolGirlStateType::Damaged_BlowBack);
	FSMBase::CreateState<SchoolGirlState_Damaged_KnockDown>(SchoolGirlStateType::Damaged_KnockDown);
	FSMBase::CreateState<SchoolGirlState_Damaged_WallHit>(SchoolGirlStateType::Damaged_WallHit);
	FSMBase::CreateState<SchoolGirlState_Damaged_WallOut>(SchoolGirlStateType::Damaged_WallOut);
	FSMBase::CreateState<SchoolGirlState_Damaged_Dazed>(SchoolGirlStateType::Damaged_Dazed);




	FSMBase::ChangeState(SchoolGirlStateType::Idle);
}
