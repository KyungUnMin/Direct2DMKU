#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"
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

	FieldActorBase::CreateColliders(CollisionOrder::PlayerMain);
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
	if (true == IsFixedDirection)
	{
		IsFixedDirection = false;
		return;
	}

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


void FieldPlayer::SetDirection(bool IsRight)
{
	RenderDir = IsRight;
	IsFixedDirection = true;

	GameEngineTransform* TransPtr = GetTransform();
	if (true == RenderDir)
	{
		TransPtr->SetLocalPositiveScaleX();
	}
	else
	{
		TransPtr->SetLocalNegativeScaleX();
	}
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



bool FieldPlayer::OnDamage(PlayerStateType _State)
{
	size_t SelectedDamageState = static_cast<size_t>(_State);
	size_t DamageStartIndex = static_cast<size_t>(PlayerStateType::NormalDamaged_Face);
	size_t DamageEndIndex = static_cast<size_t>(PlayerStateType::NormalDamaged_Jaw);

	if ((SelectedDamageState < DamageStartIndex) || (DamageEndIndex < SelectedDamageState))
	{
		MsgAssert("�÷��̾��� FSM�� ���ݹ޴� ���°� �ƴ� �ٸ� ���·� �ٲٷ��� �߽��ϴ�");
		return false;
	}

	//TODO List

	//����ϰ� �ִ� �����϶�,

	//�̹� ���ݹް� �ִ� �����϶�,

	//�и����϶�

	//����׿� ���ñ� ���


	Fsm.ChangeState(SelectedDamageState);
	return true;
}