#include "PrecompileHeader.h"
#include "PlayerState_Jump.h"
#include <algorithm>
#include "FieldPlayer.h"
#include "PlayerFSM.h"


PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}



void PlayerState_Jump::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	LiveTime += _DeltaTime;
	float Ratio = (LiveTime / Duration);

	float NowJumpScale = JumpScale * (1.f - Ratio);
	//GetPlayerPtr()->AddHeight(NowJumpScale * _DeltaTime);
	
	if (Duration < LiveTime)
	{
		GetFSM()->ChangeState(PlayerStateType::Fall);
		return;
	}

	Update_Move(_DeltaTime);
}

void PlayerState_Jump::ExitState()
{
	PlayerStateBase::ExitState();
	LiveTime = 0.f;
}
