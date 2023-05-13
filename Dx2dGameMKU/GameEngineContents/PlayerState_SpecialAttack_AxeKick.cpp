#include "PrecompileHeader.h"
#include "PlayerState_SpecialAttack_AxeKick.h"


#include "PlayerFSM.h"

const std::string_view PlayerState_SpecialAttack_AxeKick::AniName = "SpecialAttack_AxeKick";
const std::string_view PlayerState_SpecialAttack_AxeKick::AniFileName = "Player_SpecialAttack_AxeKick.png";
const std::pair<int, int> PlayerState_SpecialAttack_AxeKick::AniCutFrame = std::pair<int, int>(4, 5);
const float PlayerState_SpecialAttack_AxeKick::AniInterTime = 0.05f;

PlayerState_SpecialAttack_AxeKick::PlayerState_SpecialAttack_AxeKick()
{

}

PlayerState_SpecialAttack_AxeKick::~PlayerState_SpecialAttack_AxeKick()
{

}

void PlayerState_SpecialAttack_AxeKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_SpecialAttack_AxeKick::LoadAnimation()
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
	Dir.Move("SpecialAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_SpecialAttack_AxeKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 16,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_SpecialAttack_AxeKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_SpecialAttack_AxeKick::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
