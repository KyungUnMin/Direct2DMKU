#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_HookKick.h"


#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QuickAttack_HookKick::AniName = "QuickAttack_HookKick";
const std::string_view PlayerState_QuickAttack_HookKick::AniFileName = "Player_QuickAttack_HookKick_04.png";
const std::pair<int, int> PlayerState_QuickAttack_HookKick::AniCutFrame = std::pair<int, int>(5, 2);
const float PlayerState_QuickAttack_HookKick::AniInterTime = 0.06f;

PlayerState_QuickAttack_HookKick::PlayerState_QuickAttack_HookKick()
{

}

PlayerState_QuickAttack_HookKick::~PlayerState_QuickAttack_HookKick()
{

}

void PlayerState_QuickAttack_HookKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_HookKick::LoadAnimation()
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

void PlayerState_QuickAttack_HookKick::CreateAnimation()
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

void PlayerState_QuickAttack_HookKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_QuickAttack_HookKick::Update(float _DeltaTime)
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

	/*GetFSM()->ChangeState(PlayerStateType::QuickAttack_BackKick);
	return;*/

	//TODO
}


void PlayerState_QuickAttack_HookKick::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}
