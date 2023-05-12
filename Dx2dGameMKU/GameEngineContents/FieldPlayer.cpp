#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KeyMgr.h"

FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	//Start부분을 위해 여기서도 설정
	GPtr = this;
}

FieldPlayer::~FieldPlayer()
{
	if (this == GPtr)
	{
		GPtr = nullptr;
	}
}




void FieldPlayer::Start()
{
	FieldActorBase::Start();

	Fsm.Init();
}




void FieldPlayer::Update(float _DeltaTime) 
{
	FieldActorBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}



void FieldPlayer::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldPlayer::IsDashing() const
{
	//지금  대시 상태라면 true
	PlayerStateType NowState = Fsm.GetNowState<PlayerStateType>();
	if (PlayerStateType::Dash == NowState)
		return true;
	
	//점프나, 떨어지는 상태가 아니라면 false (Jump, Fall 일때는 따로 봐야 하는 부분이 있음)
	if ((PlayerStateType::Jump != NowState) && (PlayerStateType::Fall != NowState))
		return false;

	//지금 Jump, Fall 면서 마지막 움직임이 대시면 true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Dash == LastMoveType)
		return true;

	return false;
}
