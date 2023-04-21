#include "PrecompileHeader.h"
#include "PlayerFSM.h"

PlayerFSM::PlayerFSM()
{

}

PlayerFSM::~PlayerFSM()
{

}



void PlayerFSM::Init()
{
	FSMBase::ResizeStates(PlayerStateType::COUNT);


}
