#include "PrecompileHeader.h"
#include "TigerManState_Attack_Chop.h"

#include "DataMgr.h"

#include "TigerManFSM.h"
#include "FieldPlayer.h"

const std::string_view TigerManState_Attack_Chop::AniName = "Attack_Chop";
const std::string_view TigerManState_Attack_Chop::AniFileName = "TigerMan_Chop.png";
const std::pair<int, int> TigerManState_Attack_Chop::AniCutFrame = std::pair<int, int>(5, 2);
const float TigerManState_Attack_Chop::AniInterTime = 0.08f;
const int TigerManState_Attack_Chop::Damage = 8;

TigerManState_Attack_Chop::TigerManState_Attack_Chop()
{

}

TigerManState_Attack_Chop::~TigerManState_Attack_Chop()
{

}

void TigerManState_Attack_Chop::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void TigerManState_Attack_Chop::LoadAnimation()
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

void TigerManState_Attack_Chop::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}


void TigerManState_Attack_Chop::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void TigerManState_Attack_Chop::Update(float _DeltaTime)
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



void TigerManState_Attack_Chop::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
