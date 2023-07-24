#include "PrecompileHeader.h"
#include "CopState_Attack_BatonSmash.h"

#include "CopFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view CopState_Attack_BatonSmash::AniName = "Attack_BatonSmack";
const std::string_view CopState_Attack_BatonSmash::AniFileName = "Cop_BatonSmack.png";
const std::pair<int, int> CopState_Attack_BatonSmash::AniCutFrame = std::pair<int, int>(5, 3);
const float CopState_Attack_BatonSmash::AniInterTime = 0.06f;
const int CopState_Attack_BatonSmash::Damage = 5;

CopState_Attack_BatonSmash::CopState_Attack_BatonSmash()
{

}

CopState_Attack_BatonSmash::~CopState_Attack_BatonSmash()
{

}

void CopState_Attack_BatonSmash::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CopState_Attack_BatonSmash::LoadAnimation()
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

void CopState_Attack_BatonSmash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 4);
}




void CopState_Attack_BatonSmash::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void CopState_Attack_BatonSmash::Update(float _DeltaTime)
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
	CopStateType RandomAttack = static_cast<CopStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<CopStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(CopStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}


void CopState_Attack_BatonSmash::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Stomach(Damage);
	
}
