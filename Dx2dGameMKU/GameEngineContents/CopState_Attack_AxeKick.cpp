#include "PrecompileHeader.h"
#include "CopState_Attack_AxeKick.h"

#include "CopFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view CopState_Attack_AxeKick::AniName = "Attack_AxeKick";
const std::string_view CopState_Attack_AxeKick::AniFileName = "Cop_Axe_Kick.png";
const std::pair<int, int> CopState_Attack_AxeKick::AniCutFrame = std::pair<int, int>(5, 2);
const float CopState_Attack_AxeKick::AniInterTime = 0.08f;
const int CopState_Attack_AxeKick::Damage = 5;

CopState_Attack_AxeKick::CopState_Attack_AxeKick()
{

}

CopState_Attack_AxeKick::~CopState_Attack_AxeKick()
{

}

void CopState_Attack_AxeKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CopState_Attack_AxeKick::LoadAnimation()
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

void CopState_Attack_AxeKick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}




void CopState_Attack_AxeKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void CopState_Attack_AxeKick::Update(float _DeltaTime)
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


void CopState_Attack_AxeKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Stomach();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
