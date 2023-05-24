#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_JumpKneeKick.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view SchoolGirlState_Attack_JumpKneeKick::AniName = "Attack_JumpKneeKick";
const std::string_view SchoolGirlState_Attack_JumpKneeKick::AniFileName = "SchoolGirl_JumpKneeKick.png";
const std::pair<int, int> SchoolGirlState_Attack_JumpKneeKick::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Attack_JumpKneeKick::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_JumpKneeKick::Damage = 5;
const float SchoolGirlState_Attack_JumpKneeKick::Duration = 0.5f;

SchoolGirlState_Attack_JumpKneeKick::SchoolGirlState_Attack_JumpKneeKick()
{

}

SchoolGirlState_Attack_JumpKneeKick::~SchoolGirlState_Attack_JumpKneeKick()
{

}

void SchoolGirlState_Attack_JumpKneeKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Attack_JumpKneeKick::LoadAnimation()
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

void SchoolGirlState_Attack_JumpKneeKick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}




void SchoolGirlState_Attack_JumpKneeKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void SchoolGirlState_Attack_JumpKneeKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	EnemyStateBase::Update_SinJump(Duration);

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


void SchoolGirlState_Attack_JumpKneeKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
