#include "PrecompileHeader.h"
#include "HooliganState_Attack_DodgeKick.h"

#include "SoundMgr.h"
#include "DataMgr.h"

#include "HooliganFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"

const std::string_view HooliganState_Attack_DodgeKick::AniName = "Attack_DodgeKick";
const std::string_view HooliganState_Attack_DodgeKick::AniFileName = "Hooligan_DodgeKick.png";
const std::pair<int, int> HooliganState_Attack_DodgeKick::AniCutFrame = std::pair<int, int>(5, 4);
const float HooliganState_Attack_DodgeKick::AniInterTime = 0.05f;
const int HooliganState_Attack_DodgeKick::Damage = 5;

HooliganState_Attack_DodgeKick::HooliganState_Attack_DodgeKick()
{

}

HooliganState_Attack_DodgeKick::~HooliganState_Attack_DodgeKick()
{

}

void HooliganState_Attack_DodgeKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();

}

void HooliganState_Attack_DodgeKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Hooligan");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void HooliganState_Attack_DodgeKick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 18,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 11);
	EnemyState_AttackBase::SetMoveEvent(AniName, 9);

	Render->SetAnimationStartEvent(AniName, 10, []()
	{
		SoundMgr::PlaySFX("Hooligan_DodgeKick_Effect.wav");
	});
}


void HooliganState_Attack_DodgeKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();

	//처음엔 바라보고 있는 시선 뒤쪽으로 점프한다
	BackMoveDir = EnemyStateBase::IsRightDir() ? float4::Left : float4::Right;
}



void HooliganState_Attack_DodgeKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	Update_BackMove(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(HooliganStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	HooliganStateType RandomAttack = static_cast<HooliganStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<HooliganStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(HooliganStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}

void HooliganState_Attack_DodgeKick::Update_BackMove(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	if (BackMoveDuration < LiveTime)
		return;

	float Ratio = std::clamp(LiveTime / BackMoveDuration, 0.f, 1.f);
	EnemyState_AttackBase::Update_AccMove(_DeltaTime, Ratio, BackMoveDir, MaxBackAcc);
}



void HooliganState_Attack_DodgeKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(Damage);

}
