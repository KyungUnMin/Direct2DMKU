#include "PrecompileHeader.h"
#include "SchoolBoyFSM.h"

#include "SchoolBoyState_Idle.h"
#include "SchoolBoyState_Walk.h"


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


	FSMBase::ChangeState(SchoolBoyStateType::Idle);
}
