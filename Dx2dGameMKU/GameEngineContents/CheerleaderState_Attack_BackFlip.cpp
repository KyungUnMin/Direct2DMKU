#include "PrecompileHeader.h"
#include "CheerleaderState_Attack_BackFlip.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"

const std::string_view CheerleaderState_Attack_BackFlip::AniName = "Attack_BackFlip";
const std::string_view CheerleaderState_Attack_BackFlip::AniFileName = "Cheerleader_BackFlip.png";
const std::pair<int, int> CheerleaderState_Attack_BackFlip::AniCutFrame = std::pair<int, int>(5, 5);
const float CheerleaderState_Attack_BackFlip::AniInterTime = 0.05f;
const int CheerleaderState_Attack_BackFlip::Damage = 5;

CheerleaderState_Attack_BackFlip::CheerleaderState_Attack_BackFlip()
{

}

CheerleaderState_Attack_BackFlip::~CheerleaderState_Attack_BackFlip()
{

}

void CheerleaderState_Attack_BackFlip::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Attack_BackFlip::LoadAnimation()
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

void CheerleaderState_Attack_BackFlip::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 21,
		.FrameInter = AniInterTime,
		.Loop = false,
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 7);
	EnemyState_AttackBase::SetMoveEvent(AniName, 6, true);

	EnemyRender->SetAnimationStartEvent(AniName, 12, [this]()
	{
		this->Jump();
	});

	EnemyRender->SetAnimationStartEvent(AniName, 14, []()
	{
		SoundMgr::PlaySFX("CheerLeader_BackFlip.wav");
	});
}




void CheerleaderState_Attack_BackFlip::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(ColOffset, ColSize);
}





void CheerleaderState_Attack_BackFlip::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == JumpValue)
		return;

	float Timer = GetLiveTime() - JumpStartTime;
	EnemyStateBase::Update_SinJump(Timer, JumpDuration, MaxJumpHeight);

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


void CheerleaderState_Attack_BackFlip::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw(Damage);
}


void CheerleaderState_Attack_BackFlip::ExitState()
{
	EnemyState_AttackBase::ExitState();
	JumpValue = false;
}
