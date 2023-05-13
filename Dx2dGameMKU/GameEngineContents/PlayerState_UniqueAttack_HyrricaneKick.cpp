#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"


#include "PlayerFSM.h"

const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniName = "UniqueAttack_HyrricaneKick";
const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniFileName = "Player_UniqueAttack_HyrricaneKick.png";
const std::pair<int, int> PlayerState_UniqueAttack_HyrricaneKick::AniCutFrame = std::pair<int, int>(7, 4);
const float PlayerState_UniqueAttack_HyrricaneKick::AniInterTime = 0.05f;

PlayerState_UniqueAttack_HyrricaneKick::PlayerState_UniqueAttack_HyrricaneKick()
{

}

PlayerState_UniqueAttack_HyrricaneKick::~PlayerState_UniqueAttack_HyrricaneKick()
{

}

void PlayerState_UniqueAttack_HyrricaneKick::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_UniqueAttack_HyrricaneKick::LoadAnimation()
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
	Dir.Move("UniqueAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_UniqueAttack_HyrricaneKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 23,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_UniqueAttack_HyrricaneKick::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_UniqueAttack_HyrricaneKick::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
