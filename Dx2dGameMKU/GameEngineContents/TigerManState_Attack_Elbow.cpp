#include "PrecompileHeader.h"
#include "TigerManState_Attack_Elbow.h"

#include "DataMgr.h"

#include "TigerManFSM.h"
#include "FieldPlayer.h"

const std::string_view TigerManState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view TigerManState_Attack_Elbow::AniFileName = "TigerMan_Elbow_Uppercut.png";
const std::pair<int, int> TigerManState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 2);
const float TigerManState_Attack_Elbow::AniInterTime = 0.08f;
const int TigerManState_Attack_Elbow::Damage = 5;

TigerManState_Attack_Elbow::TigerManState_Attack_Elbow()
{

}

TigerManState_Attack_Elbow::~TigerManState_Attack_Elbow()
{

}

void TigerManState_Attack_Elbow::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void TigerManState_Attack_Elbow::LoadAnimation()
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

void TigerManState_Attack_Elbow::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}


void TigerManState_Attack_Elbow::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void TigerManState_Attack_Elbow::Update(float _DeltaTime)
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
	TigerManStateType RandomAttack = TigerManFSM::GetRandomAttack();
	if (GetStateEnum<TigerManStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(TigerManStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void TigerManState_Attack_Elbow::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
