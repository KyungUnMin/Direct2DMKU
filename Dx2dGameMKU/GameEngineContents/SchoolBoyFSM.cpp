#include "PrecompileHeader.h"
#include "SchoolBoyFSM.h"

//Movement
#include "SchoolBoyState_Idle.h"
#include "SchoolBoyState_Walk.h"
#include "SchoolBoyState_Ready.h"

//Attack
#include "SchoolBoyState_Attack_AxeKick.h"
#include "SchoolBoyState_Attack_Elbow.h"
#include "SchoolBoyState_Attack_Punch.h"
#include "SchoolBoyState_Attack_SideKick.h"


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



	FSMBase::ChangeState(SchoolBoyStateType::Idle);
}
