#include "PrecompileHeader.h"
#include "PlayerState_AttackBase.h"

PlayerState_AttackBase::PlayerState_AttackBase()
{

}

PlayerState_AttackBase::~PlayerState_AttackBase()
{

}

void PlayerState_AttackBase::Start()
{
	PlayerStateBase::Start();
	PlayerStateBase::DirChangeOff();
}

