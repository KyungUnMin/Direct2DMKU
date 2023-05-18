#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"


#include "DataMgr.h"
#include "FieldCamController.h"

#include "PlayerFSM.h"
#include "FieldLevelBase.h"

const int PlayerState_UniqueAttack_HyrricaneKick::NeedMp = 30;

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
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
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
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	DataMgr::MinusPlayerMP(NeedMp);

	CamCtrl->SetShakeState(0.5f);
}




void PlayerState_UniqueAttack_HyrricaneKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}
