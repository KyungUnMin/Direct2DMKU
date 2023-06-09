#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_HookKick.h"


#include "KeyMgr.h"
#include "DataMgr.h"
#include "SoundMgr.h"

#include "PlayerFSM.h"
#include "FieldEnemyBase.h"

const std::string_view PlayerState_QuickAttack_HookKick::AniName = "QuickAttack_HookKick";
const std::string_view PlayerState_QuickAttack_HookKick::AniFileName = "Player_QuickAttack_HookKick_04.png";
const std::pair<int, int> PlayerState_QuickAttack_HookKick::AniCutFrame = std::pair<int, int>(5, 2);
const float PlayerState_QuickAttack_HookKick::AniInterTime = 0.05f;
const int PlayerState_QuickAttack_HookKick::Damage = 5;

PlayerState_QuickAttack_HookKick::PlayerState_QuickAttack_HookKick()
{

}

PlayerState_QuickAttack_HookKick::~PlayerState_QuickAttack_HookKick()
{

}

void PlayerState_QuickAttack_HookKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_HookKick::LoadAnimation()
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

void PlayerState_QuickAttack_HookKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime,
		.Loop = false
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 3);
}

void PlayerState_QuickAttack_HookKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue();
	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_HookKick_Voice.wav");
	SoundMgr::PlaySFX("Player_HookKick_Effect.wav");
}




void PlayerState_QuickAttack_HookKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

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


void PlayerState_QuickAttack_HookKick::ExitState()
{
	PlayerState_AttackBase::ExitState();

	IsReserveChainAttack = false;
}

void PlayerState_QuickAttack_HookKick::Attack(FieldEnemyBase* _Enemy)
{
	DataMgr::PlusPlayerMP(Damage);
	bool Result = _Enemy->OnDamage_BlowBack(TotalDamage);
	if (true == Result)
	{
		SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
		PlayerState_AttackBase::CreateHitEffect_Jaw();
	}
}
