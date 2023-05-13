#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_SnapKick.h"

#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QuickAttack_SnapKick::AniName = "QuickAttack_SnapKick";
const std::string_view PlayerState_QuickAttack_SnapKick::AniFileName = "Player_QuickAttack_SnapKick_02.png";
const std::pair<int, int> PlayerState_QuickAttack_SnapKick::AniCutFrame = std::pair<int, int>(4, 2);
const float PlayerState_QuickAttack_SnapKick::AniInterTime = 0.06f;

PlayerState_QuickAttack_SnapKick::PlayerState_QuickAttack_SnapKick()
{

}

PlayerState_QuickAttack_SnapKick::~PlayerState_QuickAttack_SnapKick()
{

}


void PlayerState_QuickAttack_SnapKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_SnapKick::LoadAnimation()
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

void PlayerState_QuickAttack_SnapKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_QuickAttack_SnapKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_QuickAttack_SnapKick::Update(float _DeltaTime)
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

	GetFSM()->ChangeState(PlayerStateType::QuickAttack_BackKick);
	return;

	//TODO
}


void PlayerState_QuickAttack_SnapKick::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}