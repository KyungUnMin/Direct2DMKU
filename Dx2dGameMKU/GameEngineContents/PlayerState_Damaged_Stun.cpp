#include "PrecompileHeader.h"
#include "PlayerState_Damaged_Stun.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_Damaged_Stun::AniName = "Player_Stun.png";

PlayerState_Damaged_Stun::PlayerState_Damaged_Stun()
{

}

PlayerState_Damaged_Stun::~PlayerState_Damaged_Stun()
{

}

void PlayerState_Damaged_Stun::Start()
{
	PlayerState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_Damaged_Stun::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniName).GetFullPath(), 4, 1);
}



void PlayerState_Damaged_Stun::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = 0.1f,
		.Loop = true
	});
}


void PlayerState_Damaged_Stun::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

void PlayerState_Damaged_Stun::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

