#include "PrecompileHeader.h"
#include "TalkUIState_Wait.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "TalkUI.h"

TalkUIState_Wait::TalkUIState_Wait()
{

}

TalkUIState_Wait::~TalkUIState_Wait()
{

}

void TalkUIState_Wait::Start()
{
	TalkUIStateBase::Start();
	Collider = GetUI()->GetCollider();
}

void TalkUIState_Wait::Update(float _DeltaTime)
{
	TalkUIStateBase::Update(_DeltaTime);

	if (nullptr == Collider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX2D, ColType::SPHERE2D))
		return;

	Collider->Off();
	ChangeState(TalkUIState::FadeIn);
}