#include "PrecompileHeader.h"
#include "SchoolGirlState_Attack_Jab.h"


#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view SchoolGirlState_Attack_Jab::AniName = "Attack_Jab";
const std::string_view SchoolGirlState_Attack_Jab::AniFileName = "SchoolGirl_Jab.png";
const std::pair<int, int> SchoolGirlState_Attack_Jab::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Attack_Jab::AniInterTime = 0.08f;
const int SchoolGirlState_Attack_Jab::Damage = 5;

SchoolGirlState_Attack_Jab::SchoolGirlState_Attack_Jab()
{

}

SchoolGirlState_Attack_Jab::~SchoolGirlState_Attack_Jab()
{

}

void SchoolGirlState_Attack_Jab::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Attack_Jab::LoadAnimation()
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

void SchoolGirlState_Attack_Jab::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false,
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}




void SchoolGirlState_Attack_Jab::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void SchoolGirlState_Attack_Jab::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;



	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Idle);
		return;
	}

	//1/n�� Idle, �������� ����� �ٸ� ����
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


void SchoolGirlState_Attack_Jab::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	
}
