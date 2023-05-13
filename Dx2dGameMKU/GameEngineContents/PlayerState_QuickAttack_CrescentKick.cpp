#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_CrescentKick.h"

#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QuickAttack_CrescentKick::AniName = "QuickAttack_CrescentKick";
const std::string_view PlayerState_QuickAttack_CrescentKick::AniFileName = "Player_QuickAttack_CrescentKick_Plus.png";
const std::pair<int, int> PlayerState_QuickAttack_CrescentKick::AniCutFrame = std::pair<int, int>(5, 2);
const float PlayerState_QuickAttack_CrescentKick::AniInterTime = 0.06f;


PlayerState_QuickAttack_CrescentKick::PlayerState_QuickAttack_CrescentKick()
{

}

PlayerState_QuickAttack_CrescentKick::~PlayerState_QuickAttack_CrescentKick()
{

}

void PlayerState_QuickAttack_CrescentKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_CrescentKick::LoadAnimation()
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

void PlayerState_QuickAttack_CrescentKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_QuickAttack_CrescentKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_QuickAttack_CrescentKick::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Z))
	{
		IsReserveChainAttack = true;
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	/*if (false == IsReserveChainAttack)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}*/

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

	//TODO
}


void PlayerState_QuickAttack_CrescentKick::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}
