#include "PrecompileHeader.h"
#include "PlayerState_AttackBase.h"

#include "FieldPlayer.h"

PlayerState_AttackBase::PlayerState_AttackBase()
{

}

PlayerState_AttackBase::~PlayerState_AttackBase()
{

}

void PlayerState_AttackBase::EnterState()
{
	PlayerStateBase::EnterState();
	FieldPlayer::GetPtr()->DirCheckOff();
}

void PlayerState_AttackBase::ExitState() 
{
	PlayerStateBase::ExitState();
	FieldPlayer::GetPtr()->DirCheckOn();
}
