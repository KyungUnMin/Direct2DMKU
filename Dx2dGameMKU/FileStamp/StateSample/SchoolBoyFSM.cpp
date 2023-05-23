#include "PrecompileHeader.h"
#include "SchoolBoyFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "SchoolBoyState_Idle.h"
#include "SchoolBoyState_Walk.h"
#include "SchoolBoyState_Ready.h"

//Attack
#include "SchoolBoyState_Attack_AxeKick.h"
#include "SchoolBoyState_Attack_Elbow.h"
#include "SchoolBoyState_Attack_Punch.h"
#include "SchoolBoyState_Attack_SideKick.h"

//Damaged
#include "SchoolBoyState_NormalDamaged_Face.h"
#include "SchoolBoyState_NormalDamaged_Stomach.h"
#include "SchoolBoyState_NormalDamaged_Jaw.h"
#include "SchoolBoyState_Damaged_BlowBack.h"
#include "SchoolBoyState_Damaged_KnockDown.h"
#include "SchoolBoyState_Damaged_WallHit.h"
#include "SchoolBoyState_Damaged_WallOut.h"
#include "SchoolBoyState_Damaged_Dazed.h"


const  std::string_view SchoolBoyFSM::NormalDamaged_FileName = "SchoolBoy_Get_Hits.png";


const std::vector<SchoolBoyStateType> SchoolBoyFSM::AttackGroup =
{
	SchoolBoyStateType::AxeKick,
	SchoolBoyStateType::Elbow,
	SchoolBoyStateType::Punch,
	SchoolBoyStateType::SideKick
};

SchoolBoyStateType SchoolBoyFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return AttackGroup[RandValue];
}




SchoolBoyFSM::SchoolBoyFSM()
{

}

SchoolBoyFSM::~SchoolBoyFSM()
{

}



void SchoolBoyFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(SchoolBoyStateType::COUNT);


	//Movement
	FSMBase::CreateState<SchoolBoyState_Idle>(SchoolBoyStateType::Idle);
	FSMBase::CreateState<SchoolBoyState_Walk>(SchoolBoyStateType::Walk);
	FSMBase::CreateState<SchoolBoyState_Ready>(SchoolBoyStateType::Ready);


	//Attack
	FSMBase::CreateState<SchoolBoyState_Attack_AxeKick>(SchoolBoyStateType::AxeKick);
	FSMBase::CreateState<SchoolBoyState_Attack_Elbow>(SchoolBoyStateType::Elbow);
	FSMBase::CreateState<SchoolBoyState_Attack_Punch>(SchoolBoyStateType::Punch);
	FSMBase::CreateState<SchoolBoyState_Attack_SideKick>(SchoolBoyStateType::SideKick);


	//Damaged
	FSMBase::CreateState<SchoolBoyState_NormalDamaged_Face>(SchoolBoyStateType::NormalDamaged_Face);
	FSMBase::CreateState<SchoolBoyState_NormalDamaged_Stomach>(SchoolBoyStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<SchoolBoyState_NormalDamaged_Jaw>(SchoolBoyStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<SchoolBoyState_Damaged_BlowBack>(SchoolBoyStateType::Damaged_BlowBack);
	FSMBase::CreateState<SchoolBoyState_Damaged_KnockDown>(SchoolBoyStateType::Damaged_KnockDown);
	FSMBase::CreateState<SchoolBoyState_Damaged_WallHit>(SchoolBoyStateType::Damaged_WallHit);
	FSMBase::CreateState<SchoolBoyState_Damaged_WallOut>(SchoolBoyStateType::Damaged_WallOut);
	FSMBase::CreateState<SchoolBoyState_Damaged_Dazed>(SchoolBoyStateType::Damaged_Dazed);




	FSMBase::ChangeState(SchoolBoyStateType::Idle);
}
