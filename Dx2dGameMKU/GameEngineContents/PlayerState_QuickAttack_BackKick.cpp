#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_BackKick.h"

#include "KeyMgr.h"
#include "DataMgr.h"
#include "SoundMgr.h"
#include "SkillMgr.h"

#include "PlayerFSM.h"
#include "FieldEnemyBase.h"

const std::string_view PlayerState_QuickAttack_BackKick::AniName = "QuickAttack_BackKick";
const std::string_view PlayerState_QuickAttack_BackKick::AniFileName = "Player_QuickAttack_BackKick_03.png";
const std::pair<int, int> PlayerState_QuickAttack_BackKick::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_QuickAttack_BackKick::AniInterTime = 0.05f;
const int PlayerState_QuickAttack_BackKick::Damage = 5;

PlayerState_QuickAttack_BackKick::PlayerState_QuickAttack_BackKick()
{

}

PlayerState_QuickAttack_BackKick::~PlayerState_QuickAttack_BackKick()
{

}

void PlayerState_QuickAttack_BackKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_BackKick::LoadAnimation()
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

void PlayerState_QuickAttack_BackKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
		});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 4);
}

void PlayerState_QuickAttack_BackKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue();
	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_BackKick_Voice.wav");
	SoundMgr::PlaySFX("Player_BackKick_Effect.wav");
}




void PlayerState_QuickAttack_BackKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);
	PlayerState_AttackBase::Update_QuickAttackMove(_DeltaTime);

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

	PlayerStateType NextAttack = PlayerStateType::QuickAttack_HookKick;
	if (true == SkillMgr::HasSkill(PlayerStateType::QuickAttack_CrescentKick))
	{
		NextAttack = PlayerStateType::QuickAttack_CrescentKick;
	}

	GetFSM()->ChangeState(NextAttack);
	return;

	//TODO
}


void PlayerState_QuickAttack_BackKick::ExitState()
{
	PlayerState_AttackBase::ExitState();

	IsReserveChainAttack = false;
}

void PlayerState_QuickAttack_BackKick::Attack(FieldEnemyBase* _Enemy)
{
	DataMgr::PlusPlayerMP(2);
	

	bool Result = _Enemy->OnDamage_Jaw(TotalDamage);
	if (true == Result)
	{
		SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
		PlayerState_AttackBase::CreateHitEffect_Jaw();
	}
}
