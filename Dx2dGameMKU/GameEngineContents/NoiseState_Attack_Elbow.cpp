#include "PrecompileHeader.h"
#include "NoiseState_Attack_Elbow.h"

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "FieldPlayer.h"

const std::string_view NoiseState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view NoiseState_Attack_Elbow::AniFileName = "Noise_Elbow.png";
const std::pair<int, int> NoiseState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 3);
const float NoiseState_Attack_Elbow::AniInterTime = 0.08f;
const int NoiseState_Attack_Elbow::Damage = 5;

NoiseState_Attack_Elbow::NoiseState_Attack_Elbow()
{

}

NoiseState_Attack_Elbow::~NoiseState_Attack_Elbow()
{

}

void NoiseState_Attack_Elbow::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Attack_Elbow::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Attack_Elbow::CreateAnimation()
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


void NoiseState_Attack_Elbow::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void NoiseState_Attack_Elbow::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(NoiseStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	NoiseStateType RandomAttack = static_cast<NoiseStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<NoiseStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(NoiseStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void NoiseState_Attack_Elbow::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
