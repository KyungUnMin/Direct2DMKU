#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"
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

	//GetRenderer()->GetTransform()->SetLocalScale(float4{ 200.f, 200.f } * 2.5f);
	Fsm.Init();
}




void FieldPlayer::Update(float _DeltaTime) 
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldActorBase::Update(_DeltaTime);
	CheckDirection();
	Fsm.Update(_DeltaTime);
}


void FieldPlayer::CheckDirection()
{
	//�̹� �������� �÷��̾� ����, true�϶� ������, false�� ����
	bool NowDir = RenderDir;

	if (true == KeyMgr::IsPress(KeyNames::RightArrow))
	{
		NowDir = true;
	}
	else if (true == KeyMgr::IsPress(KeyNames::LeftArrow))
	{
		NowDir = false;
	}

	RenderDir = NowDir;
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
	if (PlayerStateType::Movement_Dash == NowState)
		return true;
	
	//������, �������� ���°� �ƴ϶�� false (Jump, Fall �϶��� ���� ���� �ϴ� �κ��� ����)
	if ((PlayerStateType::Movement_Jump != NowState) && (PlayerStateType::Movement_Fall != NowState))
		return false;

	//���� Jump, Fall �鼭 ������ �������� ��ø� true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Movement_Dash == LastMoveType)
		return true;

	return false;
}
