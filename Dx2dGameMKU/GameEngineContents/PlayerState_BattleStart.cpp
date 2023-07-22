#include "PrecompileHeader.h"
#include "PlayerState_BattleStart.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "DataMgr.h"


const std::string_view PlayerState_BattleStart::AniFileName = "Player_BattleStart.png";
const std::string_view PlayerState_BattleStart::AniName_Fall = "BattleStart_Fall";
const std::string_view PlayerState_BattleStart::AniName_Ready = "BattleStart_Ready";



PlayerState_BattleStart::PlayerState_BattleStart()
{

}

PlayerState_BattleStart::~PlayerState_BattleStart()
{

}


void PlayerState_BattleStart::Start() 
{
	PlayerState_MovementBase::Start();

	LoadAnimation();
	CreateAnimation();

	PlayerMainCollider = FieldPlayer::GetPtr()->GetMainCollider();
	PlayerStateBase::DirChangeOff();
}

void PlayerState_BattleStart::LoadAnimation()
{
	if (nullptr != GameEngineSprite::Find(AniFileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 5, 6);
}


void PlayerState_BattleStart::CreateAnimation() 
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName_Fall,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 4,
		.FrameInter = 0.1f,
		.Loop = true,
	});

	Render->CreateAnimation
	({
		.AnimationName = AniName_Ready,
		.SpriteName = AniFileName,
		.Start = 5,
		.End = 25,
		.FrameInter = 0.08f,
		.Loop = false,
	});
}



void PlayerState_BattleStart::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName_Fall);
	PlayerMainCollider->Off();

	DataMgr::SetPlayerHP(DataMgr::PlayerFullPoint);
	DataMgr::SetPlayerMP(0);
	DataMgr::SetPlayerMoney(0);
}



void PlayerState_BattleStart::Update(float _DeltaTime) 
{
	PlayerState_MovementBase::Update(_DeltaTime);

	switch (CurState)
	{
	case PlayerState_BattleStart::State::Fall:
		Update_Fall(_DeltaTime);
		break;
	case PlayerState_BattleStart::State::Ready:
		Update_Ready(_DeltaTime);
		break;
	}
}

void PlayerState_BattleStart::Update_Fall(float _DeltaTime)
{
	float Ratio = GetLiveTime() / FallDuration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float NowHeight = (FallStartHeight * (1.f - ClampRatio));

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	Player->SetHeight(NowHeight);

	if (Ratio < 1.f)
		return;

	Player->SetHeight(0.f);
	GetRenderer()->ChangeAnimation(AniName_Ready);
	CurState = State::Ready;
}

void PlayerState_BattleStart::Update_Ready(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}


void PlayerState_BattleStart::ExitState()
{
	PlayerState_MovementBase::ExitState();
	CurState = State::Fall;
	PlayerMainCollider->On();
}