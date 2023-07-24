#include "PrecompileHeader.h"
#include "HooliganState_Attack_SnapKick.h"

#include "DataMgr.h"

#include "HooliganFSM.h"
#include "FieldPlayer.h"

const std::string_view HooliganState_Attack_SnapKick::AniName = "Attack_SnapKick";
const std::string_view HooliganState_Attack_SnapKick::AniFileName = "Hooligan_SnapKick.png";
const std::pair<int, int> HooliganState_Attack_SnapKick::AniCutFrame = std::pair<int, int>(5, 2);
const float HooliganState_Attack_SnapKick::AniInterTime = 0.08f;
const int HooliganState_Attack_SnapKick::Damage = 5;

HooliganState_Attack_SnapKick::HooliganState_Attack_SnapKick()
{

}

HooliganState_Attack_SnapKick::~HooliganState_Attack_SnapKick()
{

}

void HooliganState_Attack_SnapKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void HooliganState_Attack_SnapKick::LoadAnimation()
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

void HooliganState_Attack_SnapKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}


void HooliganState_Attack_SnapKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void HooliganState_Attack_SnapKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

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




void HooliganState_Attack_SnapKick::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Stomach(Damage);
	
}
