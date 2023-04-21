#include "PrecompileHeader.h"
#include "PlayerState_Fall.h"
#include "FieldPlayer.h"
#include "PlayerFSM.h"

PlayerState_Fall::PlayerState_Fall()
{

}

PlayerState_Fall::~PlayerState_Fall()
{

}


void PlayerState_Fall::Update(float _DeltaTime)
{
	NowGravity += (GravityAcc * _DeltaTime);
	//GetPlayerPtr()->AddHeight(-NowGravity * _DeltaTime);

	

	//임시, 물체 위에 올라가는 경우 고려X
	/*if (true == GetPlayerPtr()->IsGround())
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}*/

	Update_Move(_DeltaTime);
}

void PlayerState_Fall::ExitState()
{
	PlayerStateBase::ExitState();
	NowGravity = StartGravity;

}

