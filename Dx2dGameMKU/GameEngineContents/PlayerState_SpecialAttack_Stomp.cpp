#include "PrecompileHeader.h"
#include "PlayerState_SpecialAttack_Stomp.h"


#include "PlayerFSM.h"

const std::string_view PlayerState_SpecialAttack_Stomp::AniName = "SpecialAttack_Stomp";
const std::string_view PlayerState_SpecialAttack_Stomp::AniFileName = "Player_SpecialAttack_Stomp.png";
const std::pair<int, int> PlayerState_SpecialAttack_Stomp::AniCutFrame = std::pair<int, int>(5, 2);
const float PlayerState_SpecialAttack_Stomp::AniInterTime = 0.05f;

PlayerState_SpecialAttack_Stomp::PlayerState_SpecialAttack_Stomp()
{

}

PlayerState_SpecialAttack_Stomp::~PlayerState_SpecialAttack_Stomp()
{

}

void PlayerState_SpecialAttack_Stomp::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_SpecialAttack_Stomp::LoadAnimation()
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

void PlayerState_SpecialAttack_Stomp::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_SpecialAttack_Stomp::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_SpecialAttack_Stomp::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
