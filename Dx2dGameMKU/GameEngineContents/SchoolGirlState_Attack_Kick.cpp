#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_Kick.h"


#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view SchoolGirlState_Attack_Kick::AniName = "Attack_Kick";
const std::string_view SchoolGirlState_Attack_Kick::AniFileName = "SchoolGirl_Kick.png";
const std::pair<int, int> SchoolGirlState_Attack_Kick::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Attack_Kick::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_Kick::Damage = 5;

SchoolGirlState_Attack_Kick::SchoolGirlState_Attack_Kick()
{

}

SchoolGirlState_Attack_Kick::~SchoolGirlState_Attack_Kick()
{

}

void SchoolGirlState_Attack_Kick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Attack_Kick::LoadAnimation()
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

void SchoolGirlState_Attack_Kick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 7,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}




void SchoolGirlState_Attack_Kick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void SchoolGirlState_Attack_Kick::Update(float _DeltaTime)
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
	SchoolGirlStateType RandomAttack = static_cast<SchoolGirlStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<SchoolGirlStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}


void SchoolGirlState_Attack_Kick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(Damage);

}
