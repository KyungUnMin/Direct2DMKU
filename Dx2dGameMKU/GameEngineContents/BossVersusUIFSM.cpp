#include "PrecompileHeader.h"
#include "BossVersusUIFSM.h"

#include "BossVersusState_PortraitMatch.h"
#include "BossVersusState_Corner.h"
#include "BossVersusState_Spark.h"
#include "BossVersusState_CallName.h"
#include "BossVersusState_Wait.h"


BossVersusUIFSM::BossVersusUIFSM()
{

}

BossVersusUIFSM::~BossVersusUIFSM()
{

}



void BossVersusUIFSM::Init(BossVersus* _UI)
{
	FSMBase::ResizeStates(BossVersusStateType::COUNT);

	FSMBase::CreateState<BossVersusState_PortraitMatch>(BossVersusStateType::PortraitMatch);
	FSMBase::CreateState<BossVersusState_Corner>(BossVersusStateType::Corner);
	FSMBase::CreateState<BossVersusState_Spark>(BossVersusStateType::Spark);
	FSMBase::CreateState<BossVersusState_CallName>(BossVersusStateType::CallName);
	FSMBase::CreateState<BossVersusState_Wait>(BossVersusStateType::Wait);

	FSMBase::ChangeState(BossVersusStateType::PortraitMatch);
}