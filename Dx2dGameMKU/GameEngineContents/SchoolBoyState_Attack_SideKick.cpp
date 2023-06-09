#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_SideKick.h"

#include "DataMgr.h"

#include "SchoolBoyFSM.h"
#include "FieldPlayer.h"

const std::string_view SchoolBoyState_Attack_SideKick::AniName = "Attack_SideKick";
const std::string_view SchoolBoyState_Attack_SideKick::AniFileName = "SchoolBoy_Side_Kick.png";
const std::pair<int, int> SchoolBoyState_Attack_SideKick::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_SideKick::AniInterTime = 0.08f;
const int SchoolBoyState_Attack_SideKick::Damage = 5;

SchoolBoyState_Attack_SideKick::SchoolBoyState_Attack_SideKick()
{

}

SchoolBoyState_Attack_SideKick::~SchoolBoyState_Attack_SideKick()
{

}

void SchoolBoyState_Attack_SideKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_SideKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Attack_SideKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
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


void SchoolBoyState_Attack_SideKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void SchoolBoyState_Attack_SideKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(SchoolBoyStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	SchoolBoyStateType RandomAttack = static_cast<SchoolBoyStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<SchoolBoyStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(SchoolBoyStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}




void SchoolBoyState_Attack_SideKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
