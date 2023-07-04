#include "PrecompileHeader.h"
#include "PlayerState_Damaged_Stun.h"

#include "SoundMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_Damaged_Stun::AniFileName = "Player_Stun.png";
const std::string_view PlayerState_Damaged_Stun::EnterAniName = "StunEnter";
const std::string_view PlayerState_Damaged_Stun::LoopAniName = "StunLoop";


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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 4, 2);
}



void PlayerState_Damaged_Stun::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = EnterAniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 3,
		.FrameInter = 0.08f,
		.Loop = false
	});

	Render->CreateAnimation
	({
		.AnimationName = LoopAniName,
		.SpriteName = AniFileName,
		.Start = 4,
		.End = 7,
		.FrameInter = 0.1f,
		.Loop = true
	});
}


void PlayerState_Damaged_Stun::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(EnterAniName);
	SoundMgr::PlaySFX("Player_Stun_Effect.wav").SetVolume(0.5f);
}

void PlayerState_Damaged_Stun::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	switch (CurState)
	{
	case PlayerState_Damaged_Stun::State::Enter:
		Update_Enter();
		break;
	case PlayerState_Damaged_Stun::State::Loop:
		Update_Loop();
		break;
	}
}

void PlayerState_Damaged_Stun::Update_Enter()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (false == Render->IsAnimationEnd())
		return;

	Render->ChangeAnimation(LoopAniName);
	CurState = State::Loop;
}

void PlayerState_Damaged_Stun::Update_Loop() 
{
	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}


void PlayerState_Damaged_Stun::ExitState()
{
	PlayerState_DamagedBase::ExitState();
	CurState = State::Enter;
}

