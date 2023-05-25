#include "PrecompileHeader.h"
#include "CheerleaderState_Attack_Jab.h"

#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view CheerleaderState_Attack_Jab::AniName = "Attack_Jab";
const std::string_view CheerleaderState_Attack_Jab::AniFileName = "Cheerleader_Jab.png";
const std::pair<int, int> CheerleaderState_Attack_Jab::AniCutFrame = std::pair<int, int>(5, 2);
const float CheerleaderState_Attack_Jab::AniInterTime = 0.08f;
const int CheerleaderState_Attack_Jab::Damage = 5;

CheerleaderState_Attack_Jab::CheerleaderState_Attack_Jab()
{

}

CheerleaderState_Attack_Jab::~CheerleaderState_Attack_Jab()
{

}

void CheerleaderState_Attack_Jab::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Attack_Jab::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Attack_Jab::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 5,
		.FrameInter = AniInterTime
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}




void CheerleaderState_Attack_Jab::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void CheerleaderState_Attack_Jab::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;



	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(CheerleaderStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	CheerleaderStateType RandomAttack = static_cast<CheerleaderStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<CheerleaderStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(CheerleaderStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}


void CheerleaderState_Attack_Jab::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
