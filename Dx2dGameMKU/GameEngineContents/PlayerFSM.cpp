#include "PrecompileHeader.h"
#include "PlayerFSM.h"

#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Jump.h"
#include "PlayerState_Fall.h"
#include "PlayerState_Dash.h"

PlayerFSM::PlayerFSM()
{

}

PlayerFSM::~PlayerFSM()
{

}



void PlayerFSM::Init()
{
	FSMBase::ResizeStates(PlayerStateType::COUNT);
	
	FSMBase::CreateState<PlayerState_Idle>(PlayerStateType::Idle);
	FSMBase::CreateState<PlayerState_Move>(PlayerStateType::Move);
	FSMBase::CreateState<PlayerState_Jump>(PlayerStateType::Jump);
	FSMBase::CreateState<PlayerState_Fall>(PlayerStateType::Fall);
	FSMBase::CreateState<PlayerState_Dash>(PlayerStateType::Dash);

	FSMBase::ChangeState(PlayerStateType::Idle);
}

