#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_Elbow.h"

#include "DataMgr.h"

#include "SchoolGirlFSM.h"
#include "FieldPlayer.h"

const std::string_view SchoolGirlState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view SchoolGirlState_Attack_Elbow::AniFileName = "SchoolGirl_Elbow_Uppercut.png";
const std::pair<int, int> SchoolGirlState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Attack_Elbow::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_Elbow::Damage = 5;

SchoolGirlState_Attack_Elbow::SchoolGirlState_Attack_Elbow()
{

}

SchoolGirlState_Attack_Elbow::~SchoolGirlState_Attack_Elbow()
{

}

void SchoolGirlState_Attack_Elbow::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Attack_Elbow::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolGirl");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolGirlState_Attack_Elbow::CreateAnimation()
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


void SchoolGirlState_Attack_Elbow::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void SchoolGirlState_Attack_Elbow::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	SchoolGirlStateType RandomAttack = SchoolGirlFSM::GetRandomAttack();
	if (GetStateEnum<SchoolGirlStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void SchoolGirlState_Attack_Elbow::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
