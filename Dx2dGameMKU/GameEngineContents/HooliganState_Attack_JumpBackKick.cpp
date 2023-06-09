#include "PrecompileHeader.h"
#include "HooliganState_Attack_JumpBackKick.h"

#include "DataMgr.h"

#include "HooliganFSM.h"
#include "FieldPlayer.h"

const std::string_view HooliganState_Attack_JumpBackKick::AniName = "Attack_JumpBackKick";
const std::string_view HooliganState_Attack_JumpBackKick::AniFileName = "Hooligan_JumpBackKick.png";
const std::pair<int, int> HooliganState_Attack_JumpBackKick::AniCutFrame = std::pair<int, int>(5, 3);
const float HooliganState_Attack_JumpBackKick::AniInterTime = 0.08f;
const int HooliganState_Attack_JumpBackKick::Damage = 5;

HooliganState_Attack_JumpBackKick::HooliganState_Attack_JumpBackKick()
{

}

HooliganState_Attack_JumpBackKick::~HooliganState_Attack_JumpBackKick()
{

}

void HooliganState_Attack_JumpBackKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void HooliganState_Attack_JumpBackKick::LoadAnimation()
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

void HooliganState_Attack_JumpBackKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 12,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}


void HooliganState_Attack_JumpBackKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void HooliganState_Attack_JumpBackKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	EnemyState_AttackBase::Update_SinJump(0.5f, 30.f);

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



void HooliganState_Attack_JumpBackKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}