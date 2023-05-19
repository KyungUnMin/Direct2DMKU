#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"


#include "DataMgr.h"
#include "FieldCamController.h"

#include "PlayerFSM.h"
#include "FieldLevelBase.h"
#include "FieldEnemyBase.h"

const int PlayerState_UniqueAttack_HyrricaneKick::NeedMp = 30;

const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniName = "UniqueAttack_HyrricaneKick";
const std::string_view PlayerState_UniqueAttack_HyrricaneKick::AniFileName = "Player_UniqueAttack_HyrricaneKick.png";
const std::pair<int, int> PlayerState_UniqueAttack_HyrricaneKick::AniCutFrame = std::pair<int, int>(7, 4);
const float PlayerState_UniqueAttack_HyrricaneKick::AniInterTime = 0.05f;
const int PlayerState_UniqueAttack_HyrricaneKick::Damage = 10;


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

	//나중에 Attack함수 내에서 인트로 구분한다거나 하자
	for (size_t i = 5; i < 20; ++i)
	{
		PlayerState_AttackBase::SetAttackCheckFrame(AniName, i);
	}
}

void PlayerState_UniqueAttack_HyrricaneKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	DataMgr::MinusPlayerMP(NeedMp);
	PlayerState_AttackBase::SetAttackColValue(float4::Zero, float4::One * 200.f);
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



void PlayerState_UniqueAttack_HyrricaneKick::Attack(FieldEnemyBase* _Enemy)
{
	//처음 공격을 맞췄을때
	if (false == IsHit)
	{
		CamCtrl->SetShakeState(0.5f);
		IsHit = true;
	}

	size_t CurFrame = GetRenderer()->GetCurrentFrame();
	if (19 == CurFrame)
	{
		_Enemy->OnDamage_BlowBack(Damage);
	}
	else if (0 == (CurFrame % 2))
	{
		_Enemy->OnDamage_Face(Damage);
	}
	else
	{
		_Enemy->OnDamage_Jaw(Damage);
	}

}

void PlayerState_UniqueAttack_HyrricaneKick::ExitState()
{
	PlayerState_AttackBase::ExitState();
	IsHit = false;
}


