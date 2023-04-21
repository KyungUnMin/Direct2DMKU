#include "PrecompileHeader.h"
#include "PlayerStateIdle.h"
#include "KeyMgr.h"
#include "PlayerFSM.h"

PlayerStateIdle::PlayerStateIdle()
{

}

PlayerStateIdle::~PlayerStateIdle()
{

}

void PlayerStateIdle::Start()
{
	PlayerStateBase::Start();

	ArrowKeyNames.reserve(4);
	ArrowKeyNames.push_back(KeyNames::UpArrow);
	ArrowKeyNames.push_back(KeyNames::DownArrow);
	ArrowKeyNames.push_back(KeyNames::RightArrow);
	ArrowKeyNames.push_back(KeyNames::LeftArrow);
}

void PlayerStateIdle::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	for (KeyNames Arrow : ArrowKeyNames)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

}
