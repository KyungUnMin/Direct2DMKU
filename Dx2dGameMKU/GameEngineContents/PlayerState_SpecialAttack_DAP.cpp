#include "PrecompileHeader.h"
#include "PlayerState_SpecialAttack_DAP.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_SpecialAttack_DAP::AniName = "SpecialAttack_DAP";
const std::string_view PlayerState_SpecialAttack_DAP::AniFileName = "Player_SpecialAttack_DAP.png";
const std::pair<int, int> PlayerState_SpecialAttack_DAP::AniCutFrame = std::pair<int, int>(5, 5);
const float PlayerState_SpecialAttack_DAP::AniInterTime = 0.05f;

PlayerState_SpecialAttack_DAP::PlayerState_SpecialAttack_DAP()
{

}

PlayerState_SpecialAttack_DAP::~PlayerState_SpecialAttack_DAP()
{

}

void PlayerState_SpecialAttack_DAP::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_SpecialAttack_DAP::LoadAnimation()
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

void PlayerState_SpecialAttack_DAP::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_SpecialAttack_DAP::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_SpecialAttack_DAP::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
