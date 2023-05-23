#include "PrecompileHeader.h"
#include "CopState_Attack_Punch.h"

#include "DataMgr.h"

#include "CopFSM.h"
#include "FieldPlayer.h"

const std::string_view CopState_Attack_Punch::AniName = "Attack_Punch";
const std::string_view CopState_Attack_Punch::AniFileName = "Cop_Punch.png";
const std::pair<int, int> CopState_Attack_Punch::AniCutFrame = std::pair<int, int>(5, 2);
const float CopState_Attack_Punch::AniInterTime = 0.08f;
const int CopState_Attack_Punch::Damage = 5;

CopState_Attack_Punch::CopState_Attack_Punch()
{

}

CopState_Attack_Punch::~CopState_Attack_Punch()
{

}

void CopState_Attack_Punch::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CopState_Attack_Punch::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cop");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CopState_Attack_Punch::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}


void CopState_Attack_Punch::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void CopState_Attack_Punch::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(CopStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	CopStateType RandomAttack = CopFSM::GetRandomAttack();
	if (GetStateEnum<CopStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(CopStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void CopState_Attack_Punch::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}