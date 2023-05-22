#include "PrecompileHeader.h"
#include "PlayerState_Dash.h"

#include "KeyMgr.h"
#include "PlayerFSM.h"
#include "FieldPlayer.h"

const float4 PlayerState_Dash::DashSpeed = float4{ 800.f, 400.f };

const std::string_view PlayerState_Dash::AniName = "Dash";
const std::string_view PlayerState_Dash::AniFileName = "Player_Dash.png";
const std::pair<int, int> PlayerState_Dash::AniCutFrame = std::pair<int, int>(4, 4);
const float PlayerState_Dash::AniInterTime = 0.04f;

PlayerState_Dash::PlayerState_Dash()
{

}

PlayerState_Dash::~PlayerState_Dash()
{

}

void PlayerState_Dash::Start()
{
	PlayerState_MovementBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_Dash::LoadAnimation()
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

void PlayerState_Dash::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Dash::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Dash::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Z))
	{
		GetFSM()->ChangeState(PlayerStateType::DashAttack_BackElbow);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::X))
	{
		GetFSM()->ChangeState(PlayerStateType::DashAttack_DropKick);
		return;
	}


	PlayerState_MovementBase::Update_Move(_DeltaTime, DashSpeed);
}

