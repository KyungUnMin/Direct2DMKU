#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_BackKick.h"

#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QuickAttack_BackKick::AniName = "QuickAttack_BackKick";
const std::string_view PlayerState_QuickAttack_BackKick::AniFileName = "Player_QuickAttack_BackKick_03.png";
const std::pair<int, int> PlayerState_QuickAttack_BackKick::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_QuickAttack_BackKick::AniInterTime = 0.06f;

PlayerState_QuickAttack_BackKick::PlayerState_QuickAttack_BackKick()
{

}

PlayerState_QuickAttack_BackKick::~PlayerState_QuickAttack_BackKick()
{

}

void PlayerState_QuickAttack_BackKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_BackKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("QuickAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_QuickAttack_BackKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
		});
}

void PlayerState_QuickAttack_BackKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_QuickAttack_BackKick::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Z))
	{
		IsReserveChainAttack = true;
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (false == IsReserveChainAttack)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	GetFSM()->ChangeState(PlayerStateType::QuickAttack_HookKick);
	return;

	//TODO
}


void PlayerState_QuickAttack_BackKick::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}
