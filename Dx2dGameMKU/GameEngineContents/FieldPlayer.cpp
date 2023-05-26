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

	//이번 프레임의 플레이어 방향, true일때 오른쪽, false면 왼쪽
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
	//지금  대시 상태라면 true
	PlayerStateType NowState = Fsm.GetNowState<PlayerStateType>();
	if (PlayerStateType::Movement_Dash == NowState)
		return true;
	
	//점프나, 떨어지는 상태가 아니라면 false (Jump, Fall 일때는 따로 봐야 하는 부분이 있음)
	if ((PlayerStateType::Movement_Jump != NowState) && (PlayerStateType::Movement_Fall != NowState))
		return false;

	//지금 Jump, Fall 면서 마지막 움직임이 대시면 true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Movement_Dash == LastMoveType)
		return true;

	return false;
}







//TODO List
	//방어하고 있는 상태일때,
	//이미 공격받고 있는 상태일때,
	//패링중일때
	//디버그용 뭐시기 등등
	//공중에 떠 있을때는 멀리 나가는 Damaged


bool FieldPlayer::OnDamage_Face()
{
	if (false == CanPlayerDamage())
		return false;


	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Face));
	return true;
}

bool FieldPlayer::OnDamage_Stomach()
{
	if (false == CanPlayerDamage())
		return false;

	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Stomach));
	return true;
}

bool FieldPlayer::OnDamage_Jaw()
{
	if (false == CanPlayerDamage())
		return false;

	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Jaw));
	return true;
}

bool FieldPlayer::OnDamage_BlowBack() 
{
	if (false == CanPlayerDamage())
		return false;

	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
	return true;
}


bool FieldPlayer::CanPlayerDamage()
{
	//플레이어가 방어중일때
	if (true == Fsm.OnDamageInBlock())
		return false;

	//쓰러져있는 상태일때
	if (PlayerStateType::Damaged_BlowBack == Fsm.GetNowState<PlayerStateType>())
		return false;

	return true;
}
