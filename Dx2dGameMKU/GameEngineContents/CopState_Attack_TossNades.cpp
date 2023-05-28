#include "PrecompileHeader.h"
#include "CopState_Attack_TossNades.h"

#include "DataMgr.h"
#include "RCGEnums.h"

#include "CopFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "CopGrenade.h"

const std::string_view CopState_Attack_TossNades::AniName = "Attack_TossNades";
const std::string_view CopState_Attack_TossNades::AniFileName = "Cop_TossNades.png";
const std::pair<int, int> CopState_Attack_TossNades::AniCutFrame = std::pair<int, int>(5, 3);
const float CopState_Attack_TossNades::AniInterTime = 0.08f;

CopState_Attack_TossNades::CopState_Attack_TossNades()
{

}

CopState_Attack_TossNades::~CopState_Attack_TossNades()
{

}

void CopState_Attack_TossNades::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CopState_Attack_TossNades::LoadAnimation()
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

void CopState_Attack_TossNades::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime
	});

	Render->SetAnimationStartEvent(AniName, 6, [this]()
	{
		std::shared_ptr<CopGrenade> Grenade = FieldLevelBase::GetPtr()->CreateActor<CopGrenade>(UpdateOrder::Effect);
		this->WeaponInit(Grenade);
	});
}

void CopState_Attack_TossNades::WeaponInit(std::shared_ptr<CopGrenade> _Grenade)
{
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 EnemyPos = EnemyTrans->GetWorldPosition();
	_Grenade->GetTransform()->SetLocalPosition(EnemyPos);
	
	float4 ThrowDir = EnemyStateBase::IsRightDir() ? float4::Right : float4::Left;
	_Grenade->Init(ThrowDir);
}


void CopState_Attack_TossNades::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void CopState_Attack_TossNades::Update(float _DeltaTime)
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


