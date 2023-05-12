#include "PrecompileHeader.h"
#include "PlayerState_QickAttack_Chop.h"

#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QickAttack_Chop::AniName = "QuickAttack_Chop";
const std::string_view PlayerState_QickAttack_Chop::AniFileName = "Player_QuickAttack_Chop.png";
const std::pair<int, int> PlayerState_QickAttack_Chop::AniCutFrame = std::pair<int, int>(3, 2);
const float PlayerState_QickAttack_Chop::AniInterTime = 0.08f;

PlayerState_QickAttack_Chop::PlayerState_QickAttack_Chop()
{

}

PlayerState_QickAttack_Chop::~PlayerState_QickAttack_Chop()
{

}

void PlayerState_QickAttack_Chop::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QickAttack_Chop::LoadAnimation()
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

void PlayerState_QickAttack_Chop::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}

void PlayerState_QickAttack_Chop::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_QickAttack_Chop::Update(float _DeltaTime)
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


void PlayerState_QickAttack_Chop::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}
