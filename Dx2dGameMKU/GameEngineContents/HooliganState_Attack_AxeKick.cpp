#include "PrecompileHeader.h"
#include "HooliganState_Attack_AxeKick.h"

#include "HooliganFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view HooliganState_Attack_AxeKick::AniName = "Attack_AxeKick";
const std::string_view HooliganState_Attack_AxeKick::AniFileName = "Hooligan_Axe_Kick.png";
const std::pair<int, int> HooliganState_Attack_AxeKick::AniCutFrame = std::pair<int, int>(5, 2);
const float HooliganState_Attack_AxeKick::AniInterTime = 0.08f;
const int HooliganState_Attack_AxeKick::Damage = 5;

HooliganState_Attack_AxeKick::HooliganState_Attack_AxeKick()
{

}

HooliganState_Attack_AxeKick::~HooliganState_Attack_AxeKick()
{

}

void HooliganState_Attack_AxeKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void HooliganState_Attack_AxeKick::LoadAnimation()
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

void HooliganState_Attack_AxeKick::CreateAnimation()
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




void HooliganState_Attack_AxeKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void HooliganState_Attack_AxeKick::Update(float _DeltaTime)
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
	
	HooliganStateType RandomAttack = static_cast<HooliganStateType >(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<HooliganStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(HooliganStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}


void HooliganState_Attack_AxeKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Stomach();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
