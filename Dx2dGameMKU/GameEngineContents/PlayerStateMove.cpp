#include "PrecompileHeader.h"
#include "PlayerStateMove.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "KeyMgr.h"
#include "PlayerFSM.h"
#include "FieldPlayer.h"

PlayerStateMove::PlayerStateMove()
{

}

PlayerStateMove::~PlayerStateMove()
{

}

void PlayerStateMove::Start()
{
	PlayerStateBase::Start();

	
}

void PlayerStateMove::Update(float _DeltaTime)
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

	/*if (false == FieldPlayer::GPtr->IsGround() && true == IsOnAir())
	{
		GetFSM()->ChangeState(PlayerStateType::Fall);
		return;
	}*/

	Update_Move(_DeltaTime);
}