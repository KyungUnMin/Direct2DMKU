#include "PrecompileHeader.h"
#include "PlayerStateBase.h"
#include "KeyMgr.h"

const std::vector<KeyNames> PlayerStateBase::IdleCheckKeys =
{
	KeyNames::DownArrow,
	KeyNames::UpArrow,
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::Space

};

PlayerStateBase::PlayerStateBase()
{

}

PlayerStateBase::~PlayerStateBase()
{

}

