#include "PrecompileHeader.h"
#include "PlayerFSM.h"

//Movement
#include "PlayerState_Idle.h"
#include "PlayerState_Walk.h"
#include "PlayerState_Jump.h"
#include "PlayerState_Fall.h"
#include "PlayerState_Dash.h"
#include "PlayerState_Avoid.h"

//Quick Attack
#include "PlayerState_QickAttack_Chop.h"
#include "PlayerState_QuickAttack_SnapKick.h"
#include "PlayerState_QuickAttack_BackKick.h"
#include "PlayerState_QuickAttack_HookKick.h"
#include "PlayerState_QuickAttack_CrescentKick.h"

//Special Attack
#include "PlayerState_SpecialAttack_AxeKick.h"
#include "PlayerState_SpecialAttack_DAP.h"
#include "PlayerState_SpecialAttack_DonkeyKick.h"

//Unique Attack
#include "PlayerState_UniqueAttack_DragonFeet.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"


//Dash Attack
#include "PlayerState_DashAttack_BackElbow.h"
#include "PlayerState_DashAttack_DropKick.h"


//Damaged
#include "PlayerState_NormalDamaged_Face.h"
#include "PlayerState_NormalDamaged_Stomach.h"
#include "PlayerState_NormalDamaged_Jaw.h"
#include "PlayerState_Damaged_BlowBack.h"
#include "PlayerState_Damaged_Block.h"
#include "PlayerState_Damaged_Stun.h"


size_t PlayerFSM::GetNextQuickAttack(size_t _PrevAttack)
{
	++_PrevAttack;
	if (PlayerStateType::SpecialAttack_AxeKick <= static_cast<PlayerStateType>(_PrevAttack))
	{
		_PrevAttack = static_cast<size_t>(PlayerStateType::QuickAttack_Chop);
	}

	return _PrevAttack;
}

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
	FSMBase::CreateState<PlayerState_Avoid>(PlayerStateType::Movement_Avoid);

	//Quick Attack
	FSMBase::CreateState<PlayerState_QickAttack_Chop>(PlayerStateType::QuickAttack_Chop);
	FSMBase::CreateState<PlayerState_QuickAttack_SnapKick>(PlayerStateType::QuickAttack_SnapKick);
	FSMBase::CreateState<PlayerState_QuickAttack_BackKick>(PlayerStateType::QuickAttack_BackKick);
	FSMBase::CreateState<PlayerState_QuickAttack_HookKick>(PlayerStateType::QuickAttack_HookKick);
	FSMBase::CreateState<PlayerState_QuickAttack_CrescentKick>(PlayerStateType::QuickAttack_CrescentKick);

	//Special Attack
	FSMBase::CreateState<PlayerState_SpecialAttack_AxeKick>(PlayerStateType::SpecialAttack_AxeKick);
	FSMBase::CreateState<PlayerState_SpecialAttack_DAP>(PlayerStateType::SpecialAttack_DAP);
	FSMBase::CreateState<PlayerState_SpecialAttack_DonkeyKick>(PlayerStateType::SpecialAttack_DonkeyKick);

	//Unique Attack
	FSMBase::CreateState<PlayerState_UniqueAttack_DragonFeet>(PlayerStateType::UniqueAttack_DragonFeet);
	FSMBase::CreateState<PlayerState_UniqueAttack_HyrricaneKick>(PlayerStateType::UniqueAttack_HyrricaneKick);


	//Dash Attack
	FSMBase::CreateState<PlayerState_DashAttack_BackElbow>(PlayerStateType::DashAttack_BackElbow);
	FSMBase::CreateState<PlayerState_DashAttack_DropKick>(PlayerStateType::DashAttack_DropKick);


	//Damaged
	FSMBase::CreateState<PlayerState_NormalDamaged_Face>(PlayerStateType::NormalDamaged_Face);
	FSMBase::CreateState<PlayerState_NormalDamaged_Stomach>(PlayerStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<PlayerState_NormalDamaged_Jaw>(PlayerStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<PlayerState_Damaged_BlowBack>(PlayerStateType::Damaged_BlowBack);
	FSMBase::CreateState<PlayerState_Damaged_Block>(PlayerStateType::Damaged_Block);
	FSMBase::CreateState<PlayerState_Damaged_Stun>(PlayerStateType::Damaged_Stun);





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

bool PlayerFSM::OnDamageInBlock()
{
	if (PlayerStateType::Damaged_Block != FSMBase::GetNowState<PlayerStateType>())
		return false;

	//TODO
	std::shared_ptr<PlayerState_Damaged_Block> BlockState = nullptr;
	BlockState = std::dynamic_pointer_cast<PlayerState_Damaged_Block>(FSMBase::GetNowStatePtr());
	if (nullptr == BlockState)
	{
		MsgAssert("플레이어의 FSM  Damaged_Block 슬롯에 PlayerState_Damaged_Block가 아닌 다른 State가 존재합니다");
		return false;
	}

	BlockState->OnDamage();
	return true;
}
