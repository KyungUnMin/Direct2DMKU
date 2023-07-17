#include "PrecompileHeader.h"
#include "PlayerState_QickAttack_Chop.h"

#include "KeyMgr.h"
#include "DataMgr.h"
#include "SoundMgr.h"

#include "PlayerFSM.h"
#include "FieldEnemyBase.h"

const std::string_view PlayerState_QickAttack_Chop::AniName = "QuickAttack_Chop";
const std::string_view PlayerState_QickAttack_Chop::AniFileName = "Player_QuickAttack_Chop_01.png";
const std::pair<int, int> PlayerState_QickAttack_Chop::AniCutFrame = std::pair<int, int>(3, 2);
const float PlayerState_QickAttack_Chop::AniInterTime = 0.06f;
const int PlayerState_QickAttack_Chop::Damage = 5;

PlayerState_QickAttack_Chop::PlayerState_QickAttack_Chop()
{

}

PlayerState_QickAttack_Chop::~PlayerState_QickAttack_Chop()
{

}

void PlayerState_QickAttack_Chop::Start()
{
	PlayerState_AttackBase::Start();

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
		.FrameInter = AniInterTime,
		.Loop = false
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 2);
}

void PlayerState_QickAttack_Chop::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue();
	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_Chop_Voice.wav");
	SoundMgr::PlaySFX("Player_Chop_Effect.wav");
}




void PlayerState_QickAttack_Chop::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Z))
	{
		IsReserveChainAttack = true;
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (false == IsReserveChainAttack)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	GetFSM()->ChangeState(PlayerStateType::QuickAttack_SnapKick);
	return;

	//TODO
}


void PlayerState_QickAttack_Chop::ExitState()
{
	PlayerState_AttackBase::ExitState();

	IsReserveChainAttack = false;
}




void PlayerState_QickAttack_Chop::Attack(FieldEnemyBase* _Enemy)
{
	DataMgr::PlusPlayerMP(1);

	bool Result = _Enemy->OnDamage_Face(TotalDamage);
	if(true == Result)
	{
		SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
		PlayerState_AttackBase::CreateHitEffect_Face();
	}
}
