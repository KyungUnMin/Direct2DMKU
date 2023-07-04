#include "PrecompileHeader.h"
#include "TigerManState_Attack_Boot.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "TigerManFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"


const std::string_view TigerManState_Attack_Boot::AniName = "Attack_Boot";
const std::string_view TigerManState_Attack_Boot::AniFileName = "TigerMan_Boot.png";
const std::pair<int, int> TigerManState_Attack_Boot::AniCutFrame = std::pair<int, int>(5, 3);
const float TigerManState_Attack_Boot::AniInterTime = 0.05f;
const int TigerManState_Attack_Boot::Damage = 10;

TigerManState_Attack_Boot::TigerManState_Attack_Boot()
{

}

TigerManState_Attack_Boot::~TigerManState_Attack_Boot()
{

}

void TigerManState_Attack_Boot::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void TigerManState_Attack_Boot::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_Attack_Boot::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 13,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 5);
}




void TigerManState_Attack_Boot::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void TigerManState_Attack_Boot::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;
	

	
	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(TigerManStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	TigerManStateType RandomAttack = static_cast<TigerManStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<TigerManStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(TigerManStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}


void TigerManState_Attack_Boot::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void TigerManState_Attack_Boot::OnAttackSound()
{
	SoundMgr::PlaySFX("TigerMan_Boot.wav");
}
