#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_DragonFeet.h"


#include "DataMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_UniqueAttack_DragonFeet::AniName = "UniqueAttack_DragonFeet";
const std::string_view PlayerState_UniqueAttack_DragonFeet::AniFileName = "Player_UniqueAttack_DragonFeet.png";
const std::pair<int, int> PlayerState_UniqueAttack_DragonFeet::AniCutFrame = std::pair<int, int>(7, 4);
const float PlayerState_UniqueAttack_DragonFeet::AniInterTime = 0.05f;

PlayerState_UniqueAttack_DragonFeet::PlayerState_UniqueAttack_DragonFeet()
{

}

PlayerState_UniqueAttack_DragonFeet::~PlayerState_UniqueAttack_DragonFeet()
{

}

void PlayerState_UniqueAttack_DragonFeet::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_UniqueAttack_DragonFeet::LoadAnimation()
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

void PlayerState_UniqueAttack_DragonFeet::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 21,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}

void PlayerState_UniqueAttack_DragonFeet::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	DataMgr::MinusPlayerMP(20);
}




void PlayerState_UniqueAttack_DragonFeet::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
