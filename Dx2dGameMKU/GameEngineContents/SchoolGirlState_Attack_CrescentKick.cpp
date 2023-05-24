#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_CrescentKick.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view SchoolGirlState_Attack_CrescentKick::AniName = "Attack_CrescentKick";
const std::string_view SchoolGirlState_Attack_CrescentKick::AniFileName = "SchoolGirl_CrescentKick.png";
const std::pair<int, int> SchoolGirlState_Attack_CrescentKick::AniCutFrame = std::pair<int, int>(5, 3);
const float SchoolGirlState_Attack_CrescentKick::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_CrescentKick::Damage = 5;
const float SchoolGirlState_Attack_CrescentKick::Duration = 0.8f;
const float4 SchoolGirlState_Attack_CrescentKick::ColOffset = float4::Left * 100.f;
const float4 SchoolGirlState_Attack_CrescentKick::ColSize = float4::One * 300.f;


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
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 6);
}




void SchoolGirlState_Attack_CrescentKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Left * 100.f, float4::One * 300.f);

	if (true == EnemyStateBase::IsRightDir())
	{
		EnemyDir = float4::Right;
	}
	else
	{
		EnemyDir = float4::Left;
	}
}




void SchoolGirlState_Attack_CrescentKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);


	float Ratio = (GetLiveTime() / Duration);
	EnemyStateBase::Update_AccMove(_DeltaTime, Ratio, EnemyDir, 500.f);

	if (false == GetRenderer()->IsAnimationEnd())
		return;



	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Idle);
		return;
	}

	//1/n�� Idle, �������� ����� �ٸ� ����
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


void SchoolGirlState_Attack_CrescentKick::Attack()
{
	//ù��° �����϶�
	if (0 == AttackCount)
	{
		if (true == FieldPlayer::GetPtr()->OnDamage_Stomach())
		{
			DataMgr::MinusPlayerHP(Damage);
		}

		++AttackCount;
	}

	//�ι�° �����϶�
	else
	{
		if (true == FieldPlayer::GetPtr()->OnDamage_BlowBack())
		{
			DataMgr::MinusPlayerHP(Damage * 2);
		}

		++AttackCount;
	}

}


void SchoolGirlState_Attack_CrescentKick::ExitState()
{
	EnemyState_AttackBase::ExitState();
	AttackCount = 0;
}