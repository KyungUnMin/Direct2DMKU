#include "PrecompileHeader.h"
#include "SchoolBoyFSM.h"

#include "SchoolBoyState_Idle.h"
#include "SchoolBoyState_Walk.h"
#include "SchoolBoyState_Ready.h"


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
	FSMBase::CreateState<SchoolBoyState_Idle>(SchoolBoyStateType::Idle);
	FSMBase::CreateState<SchoolBoyState_Walk>(SchoolBoyStateType::Walk);
	FSMBase::CreateState<SchoolBoyState_Ready>(SchoolBoyStateType::Ready);


	FSMBase::ChangeState(SchoolBoyStateType::Idle);
}
