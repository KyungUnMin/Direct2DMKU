#include "PrecompileHeader.h"
#include "WaverState_Attack_Kick.h"

#include "DataMgr.h"

#include "WaverFSM.h"
#include "FieldPlayer.h"

const std::string_view WaverState_Attack_Kick::AniName = "Attack_Kick";
const std::string_view WaverState_Attack_Kick::AniFileName = "Waver_Kick.png";
const std::pair<int, int> WaverState_Attack_Kick::AniCutFrame = std::pair<int, int>(5, 1);
const float WaverState_Attack_Kick::AniInterTime = 0.08f;
const int WaverState_Attack_Kick::Damage = 5;

WaverState_Attack_Kick::WaverState_Attack_Kick()
{

}

WaverState_Attack_Kick::~WaverState_Attack_Kick()
{

}

void WaverState_Attack_Kick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_Kick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void WaverState_Attack_Kick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}


void WaverState_Attack_Kick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void WaverState_Attack_Kick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(WaverStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	WaverStateType RandomAttack = static_cast<WaverStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<WaverStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(WaverStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}




void WaverState_Attack_Kick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Stomach(Damage);
	
}
