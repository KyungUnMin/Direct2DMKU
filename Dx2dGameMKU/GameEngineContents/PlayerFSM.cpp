#include "PrecompileHeader.h"
#include "PlayerFSM.h"

PlayerFSM::PlayerFSM()
{

}

PlayerFSM::~PlayerFSM()
{

}



void PlayerFSM::Init(FieldPlayer* _Player)
{
	Player = _Player;

	FSMBase::ResizeStates(PlayerStateType::COUNT);

}
