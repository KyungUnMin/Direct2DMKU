#include "PrecompileHeader.h"
#include "PlayerState_Dash.h"

#include "KeyMgr.h"
#include "PlayerFSM.h"

PlayerState_Dash::PlayerState_Dash()
{

}

PlayerState_Dash::~PlayerState_Dash()
{

}

void PlayerState_Dash::Start()
{
	PlayerStateBase::Start();


}


void PlayerState_Dash::Update(float _DeltaTime)
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




	Update_Move(_DeltaTime, DashSpeed);
}
