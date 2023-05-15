#include "PrecompileHeader.h"
#include "SchoolGirlFSM.h"

#include "SchoolGirlState_Idle.h"
#include "SchoolGirlState_Walk.h"

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
	FSMBase::CreateState<SchoolGirlState_Idle>(SchoolGirlStateType::Idle);
	FSMBase::CreateState<SchoolGirlState_Walk>(SchoolGirlStateType::Walk);


	FSMBase::ChangeState(SchoolGirlStateType::Idle);
}
