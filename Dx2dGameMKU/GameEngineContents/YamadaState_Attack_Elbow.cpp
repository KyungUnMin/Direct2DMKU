#include "PrecompileHeader.h"
#include "YamadaState_Attack_Elbow.h"

#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"

const std::string_view YamadaState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view YamadaState_Attack_Elbow::AniFileName = "Yamada_Elbow.png";
const std::pair<int, int> YamadaState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 3);
const float YamadaState_Attack_Elbow::AniInterTime = 0.08f;
const int YamadaState_Attack_Elbow::Damage = 5;

YamadaState_Attack_Elbow::YamadaState_Attack_Elbow()
{

}

YamadaState_Attack_Elbow::~YamadaState_Attack_Elbow()
{

}

void YamadaState_Attack_Elbow::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Attack_Elbow::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Attack_Elbow::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 5);
}


void YamadaState_Attack_Elbow::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void YamadaState_Attack_Elbow::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	YamadaStateType RandomAttack = static_cast<YamadaStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<YamadaStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void YamadaState_Attack_Elbow::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
