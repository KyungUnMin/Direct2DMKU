#include "PrecompileHeader.h"
#include "CheerleaderState_Attack_DoublePom.h"


#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view CheerleaderState_Attack_DoublePom::AniName = "Attack_DoublePom";
const std::string_view CheerleaderState_Attack_DoublePom::AniFileName = "Cheerleader_DoublePom.png";
const std::pair<int, int> CheerleaderState_Attack_DoublePom::AniCutFrame = std::pair<int, int>(5, 3);
const float CheerleaderState_Attack_DoublePom::AniInterTime = 0.08f;
const int CheerleaderState_Attack_DoublePom::Damage = 15;

CheerleaderState_Attack_DoublePom::CheerleaderState_Attack_DoublePom()
{

}

CheerleaderState_Attack_DoublePom::~CheerleaderState_Attack_DoublePom()
{

}

void CheerleaderState_Attack_DoublePom::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Attack_DoublePom::LoadAnimation()
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

void CheerleaderState_Attack_DoublePom::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 12,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
	EnemyState_AttackBase::SetMoveEvent(AniName, 2);
}




void CheerleaderState_Attack_DoublePom::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero, ColSize);
}



void CheerleaderState_Attack_DoublePom::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	EnemyStateBase::Update_SinJump(JumpDuration, JumpMaxHeight);

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


void CheerleaderState_Attack_DoublePom::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(Damage);
}
