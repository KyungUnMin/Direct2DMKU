#include "PrecompileHeader.h"
#include "PlayerFSM.h"

#include "PlayerState_Idle.h"
#include "PlayerState_Move.h"
#include "PlayerState_Jump.h"
#include "PlayerState_Fall.h"
#include "PlayerState_Dash.h"

#include "PlayerState_QickAttack_Chop.h"
#include "PlayerState_QuickAttack_SnapKick.h"
#include "PlayerState_QuickAttack_HookKick.h"
#include "PlayerState_QuickAttack_BackKick.h"

PlayerFSM::PlayerFSM()
{

}

PlayerFSM::~PlayerFSM()
{

}



void PlayerFSM::Init(PlayerStateType _StartState /*= PlayerStateType::Idle*/)
{
	FSMBase::ResizeStates(PlayerStateType::COUNT);
	
	//Movement
	FSMBase::CreateState<PlayerState_Idle>(PlayerStateType::Movement_Idle);
	FSMBase::CreateState<PlayerState_Move>(PlayerStateType::Movement_Move);
	FSMBase::CreateState<PlayerState_Jump>(PlayerStateType::Movement_Jump);
	FSMBase::CreateState<PlayerState_Fall>(PlayerStateType::Movement_Fall);
	FSMBase::CreateState<PlayerState_Dash>(PlayerStateType::Movement_Dash);

	//Quick Attack
	FSMBase::CreateState<PlayerState_QickAttack_Chop>(PlayerStateType::QuickAttack_Chop);
	FSMBase::CreateState<PlayerState_QuickAttack_SnapKick>(PlayerStateType::QuickAttack_SnapKick);
	FSMBase::CreateState<PlayerState_QuickAttack_HookKick>(PlayerStateType::QuickAttack_HookKick);
	FSMBase::CreateState<PlayerState_QuickAttack_BackKick>(PlayerStateType::QuickAttack_BackKick);

	
	//Special Attack


	//Damaged



	FSMBase::ChangeState(_StartState);
}

void PlayerFSM::ChangeState(size_t _NextIndex)
{
	FSMBase::ChangeState(_NextIndex);

	PlayerStateType NextState = static_cast<PlayerStateType>(_NextIndex);
	if ((PlayerStateType::Movement_Move != NextState) && (PlayerStateType::Movement_Dash != NextState))
		return;

	LastMoveState = NextState;
}

