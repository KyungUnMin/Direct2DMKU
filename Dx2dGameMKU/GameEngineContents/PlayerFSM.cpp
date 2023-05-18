#include "PrecompileHeader.h"
#include "PlayerFSM.h"

//Movement
#include "PlayerState_Idle.h"
#include "PlayerState_Walk.h"
#include "PlayerState_Jump.h"
#include "PlayerState_Fall.h"
#include "PlayerState_Dash.h"

//Quick Attack
#include "PlayerState_QickAttack_Chop.h"
#include "PlayerState_QuickAttack_SnapKick.h"
#include "PlayerState_QuickAttack_BackKick.h"
#include "PlayerState_QuickAttack_HookKick.h"
#include "PlayerState_QuickAttack_CrescentKick.h"

//Special Attack
#include "PlayerState_SpecialAttack_AxeKick.h"
#include "PlayerState_SpecialAttack_Stomp.h"
#include "PlayerState_SpecialAttack_DAP.h"

//Unique Attack
#include "PlayerState_UniqueAttack_DragonFeet.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"


//Dash Attack



//NormalDamaged
#include "PlayerState_NormalDamaged_Face.h"
#include "PlayerState_NormalDamaged_Stomach.h"
#include "PlayerState_NormalDamaged_Jaw.h"


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
	FSMBase::CreateState<PlayerState_Walk>(PlayerStateType::Movement_Walk);
	FSMBase::CreateState<PlayerState_Jump>(PlayerStateType::Movement_Jump);
	FSMBase::CreateState<PlayerState_Fall>(PlayerStateType::Movement_Fall);
	FSMBase::CreateState<PlayerState_Dash>(PlayerStateType::Movement_Dash);

	//Quick Attack
	FSMBase::CreateState<PlayerState_QickAttack_Chop>(PlayerStateType::QuickAttack_Chop);
	FSMBase::CreateState<PlayerState_QuickAttack_SnapKick>(PlayerStateType::QuickAttack_SnapKick);
	FSMBase::CreateState<PlayerState_QuickAttack_BackKick>(PlayerStateType::QuickAttack_BackKick);
	FSMBase::CreateState<PlayerState_QuickAttack_HookKick>(PlayerStateType::QuickAttack_HookKick);
	FSMBase::CreateState<PlayerState_QuickAttack_CrescentKick>(PlayerStateType::QuickAttack_CrescentKick);

	//Special Attack
	FSMBase::CreateState<PlayerState_SpecialAttack_AxeKick>(PlayerStateType::SpecialAttack_AxeKick);
	FSMBase::CreateState<PlayerState_SpecialAttack_Stomp>(PlayerStateType::SpecialAttack_Stomp);
	FSMBase::CreateState<PlayerState_SpecialAttack_DAP>(PlayerStateType::SpecialAttack_DAP);

	//Unique Attack
	FSMBase::CreateState<PlayerState_UniqueAttack_DragonFeet>(PlayerStateType::UniqueAttack_DragonFeet);
	FSMBase::CreateState<PlayerState_UniqueAttack_HyrricaneKick>(PlayerStateType::UniqueAttack_HyrricaneKick);


	//Dash Attack
	


	//NormalDamaged
	FSMBase::CreateState<PlayerState_NormalDamaged_Face>(PlayerStateType::NormalDamaged_Face);
	FSMBase::CreateState<PlayerState_NormalDamaged_Stomach>(PlayerStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<PlayerState_NormalDamaged_Jaw>(PlayerStateType::NormalDamaged_Jaw);





	FSMBase::ChangeState(_StartState);
}

void PlayerFSM::ChangeState(size_t _NextIndex)
{
	FSMBase::ChangeState(_NextIndex);

	PlayerStateType NextState = static_cast<PlayerStateType>(_NextIndex);
	if ((PlayerStateType::Movement_Walk != NextState) && (PlayerStateType::Movement_Dash != NextState))
		return;

	LastMoveState = NextState;
}

