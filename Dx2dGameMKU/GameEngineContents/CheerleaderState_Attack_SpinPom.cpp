#include "PrecompileHeader.h"
#include "CheerleaderState_Attack_SpinPom.h"

#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view CheerleaderState_Attack_SpinPom::AniName = "Attack_SpinPom";
const std::string_view CheerleaderState_Attack_SpinPom::AniFileName = "Cheerleader_SpinPom.png";
const std::pair<int, int> CheerleaderState_Attack_SpinPom::AniCutFrame = std::pair<int, int>(5, 2);
const float CheerleaderState_Attack_SpinPom::AniInterTime = 0.08f;
const int CheerleaderState_Attack_SpinPom::Damage = 10;

CheerleaderState_Attack_SpinPom::CheerleaderState_Attack_SpinPom()
{

}

CheerleaderState_Attack_SpinPom::~CheerleaderState_Attack_SpinPom()
{

}

void CheerleaderState_Attack_SpinPom::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Attack_SpinPom::LoadAnimation()
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

void CheerleaderState_Attack_SpinPom::CreateAnimation()
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

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}




void CheerleaderState_Attack_SpinPom::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void CheerleaderState_Attack_SpinPom::Update(float _DeltaTime)
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


void CheerleaderState_Attack_SpinPom::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
