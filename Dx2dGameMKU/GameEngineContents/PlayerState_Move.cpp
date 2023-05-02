#include "PrecompileHeader.h"
#include "PlayerState_Move.h"

#include "PlayerFSM.h"
#include "FieldPlayer.h"

std::vector<KeyNames>  PlayerState_Move::CheckArrows =
{
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::UpArrow,
	KeyNames::DownArrow,
};

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start()
{
	PlayerStateBase::Start();

}

void PlayerState_Move::EnterState()
{
	PlayerStateBase::EnterState();

	CheckPressArrow(PressArrow);
}



void PlayerState_Move::CheckPressArrow(KeyNames& _SettingEnum)
{
	for (const KeyNames Arrow : CheckArrows)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		_SettingEnum = Arrow;
	}
}


void PlayerState_Move::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}
	
	float NowTime = GetFSM()->GetFsmTime();
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		GetFSM()->ChangeState(PlayerStateType::Dash);
		return;
	}


	/*if (false == FieldPlayer::GPtr->IsGround() && true == IsOnAir())
	{
		GetFSM()->ChangeState(PlayerStateType::Fall);
		return;
	}*/

	PlayerStateBase::Update_Move(_DeltaTime);
}


void PlayerState_Move::ExitState()
{
	PlayerStateBase::ExitState();

	LastArrow = PressArrow;
	LastTime = GetFSM()->GetFsmTime();
}

