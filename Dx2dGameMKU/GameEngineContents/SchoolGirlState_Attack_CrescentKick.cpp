#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_CrescentKick.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"

const std::string_view SchoolGirlState_Attack_CrescentKick::AniName = "Attack_CrescentKick";
const std::string_view SchoolGirlState_Attack_CrescentKick::AniFileName = "SchoolGirl_CrescentKick.png";
const std::pair<int, int> SchoolGirlState_Attack_CrescentKick::AniCutFrame = std::pair<int, int>(5, 3);
const float SchoolGirlState_Attack_CrescentKick::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_CrescentKick::Damage = 5;

const float SchoolGirlState_Attack_CrescentKick::MoveDuration = 0.8f;
const float SchoolGirlState_Attack_CrescentKick::MoveStartAccTime = 500.f;



SchoolGirlState_Attack_CrescentKick::SchoolGirlState_Attack_CrescentKick()
{

}

SchoolGirlState_Attack_CrescentKick::~SchoolGirlState_Attack_CrescentKick()
{

}

void SchoolGirlState_Attack_CrescentKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Attack_CrescentKick::LoadAnimation()
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

void SchoolGirlState_Attack_CrescentKick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 6);
	EnemyState_AttackBase::SetMoveEvent(AniName, 2, false, MoveDuration, MoveStartAccTime);
}




void SchoolGirlState_Attack_CrescentKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(ColOffset, ColSize);
}




void SchoolGirlState_Attack_CrescentKick::Update(float _DeltaTime)
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


void SchoolGirlState_Attack_CrescentKick::Attack()
{
	//첫번째 공격일때
	if (0 == AttackCount)
	{
		if (true == FieldPlayer::GetPtr()->OnDamage_Stomach())
		{
			DataMgr::MinusPlayerHP(Damage);
		}

		++AttackCount;
	}

	//두번째 공격일때
	else
	{
		if (true == FieldPlayer::GetPtr()->OnDamage_BlowBack())
		{
			DataMgr::MinusPlayerHP(Damage * 2);
		}

		++AttackCount;
	}

}

void SchoolGirlState_Attack_CrescentKick::OnAttackSound()
{
	SoundMgr::PlaySFX("SchoolGirl_CrescentKick_Effect.wav");
}


void SchoolGirlState_Attack_CrescentKick::ExitState()
{
	EnemyState_AttackBase::ExitState();
	AttackCount = 0;
}
