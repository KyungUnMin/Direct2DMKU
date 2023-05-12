#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KeyMgr.h"

FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	//Start�κ��� ���� ���⼭�� ����
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
	//����  ��� ���¶�� true
	PlayerStateType NowState = Fsm.GetNowState<PlayerStateType>();
	if (PlayerStateType::Dash == NowState)
		return true;
	
	//������, �������� ���°� �ƴ϶�� false (Jump, Fall �϶��� ���� ���� �ϴ� �κ��� ����)
	if ((PlayerStateType::Jump != NowState) && (PlayerStateType::Fall != NowState))
		return false;

	//���� Jump, Fall �鼭 ������ �������� ��ø� true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Dash == LastMoveType)
		return true;

	return false;
}
