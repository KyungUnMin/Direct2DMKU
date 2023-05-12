#include "PrecompileHeader.h"
#include "PlayerState_Jump.h"

#include <algorithm>

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "PlayerState_Dash.h"


const std::string_view PlayerState_Jump::AniName = "Jump";
const std::string_view PlayerState_Jump::AniFileName = "Player_Jump.png";
const std::pair<int, int> PlayerState_Jump::AniCutFrame = std::pair<int, int>(3, 1);
const float PlayerState_Jump::AniInterTime = 0.08f;

PlayerState_Jump::PlayerState_Jump()
{

}

PlayerState_Jump::~PlayerState_Jump()
{

}


void PlayerState_Jump::Start()
{
	PlayerStateBase::Start();

	FsmPtr = GetConvertFSM<PlayerFSM>();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Jump::LoadAnimation()
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


void PlayerState_Jump::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}



void PlayerState_Jump::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Jump::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	float NowHeight = MaxHeight * Ratio;
	FieldPlayer::GetPtr()->SetHeight(NowHeight);

	if (1.f < Ratio)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Fall);
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

