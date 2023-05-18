#include "PrecompileHeader.h"
#include "PlayerState_Fall.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "PlayerState_Dash.h"

const std::string_view PlayerState_Fall::AniName = "Fall";
const std::string_view PlayerState_Fall::AniFileName = "Player_Fall.png";
const std::pair<int, int> PlayerState_Fall::AniCutFrame = std::pair<int, int>(2, 1);
const float PlayerState_Fall::AniInterTime = 0.08f;

PlayerState_Fall::PlayerState_Fall()
{

}

PlayerState_Fall::~PlayerState_Fall()
{

}

void PlayerState_Fall::Start()
{
	PlayerState_MovementBase::Start();

	FsmPtr = GetConvertFSM<PlayerFSM>();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Fall::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}


void PlayerState_Fall::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}



void PlayerState_Fall::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnterHeight = FieldPlayer::GetPtr()->GetHeight();
}


void PlayerState_Fall::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	float NowHeight = EnterHeight * (1.f - Ratio);
	FieldPlayer::GetPtr()->SetHeight(NowHeight);
	if (1.f < Ratio)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	if (PlayerStateType::Movement_Dash == FsmPtr->GetLastMovement())
	{
		Update_Move(_DeltaTime, PlayerState_Dash::DashSpeed);
	}
	else
	{
		Update_Move(_DeltaTime);
	}
}

