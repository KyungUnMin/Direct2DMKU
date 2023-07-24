#include "PrecompileHeader.h"
#include "WaverState_Attack_Slash.h"

#include "DataMgr.h"

#include "WaverFSM.h"
#include "FieldPlayer.h"

const std::string_view WaverState_Attack_Slash::AniName = "Attack_Slash";
const std::string_view WaverState_Attack_Slash::AniFileName = "Waver_Slash.png";
const std::pair<int, int> WaverState_Attack_Slash::AniCutFrame = std::pair<int, int>(5, 2);
const float WaverState_Attack_Slash::AniInterTime = 0.08f;
const int WaverState_Attack_Slash::Damage = 5;

WaverState_Attack_Slash::WaverState_Attack_Slash()
{

}

WaverState_Attack_Slash::~WaverState_Attack_Slash()
{

}

void WaverState_Attack_Slash::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_Slash::LoadAnimation()
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

void WaverState_Attack_Slash::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 4);
}


void WaverState_Attack_Slash::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void WaverState_Attack_Slash::Update(float _DeltaTime)
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




void WaverState_Attack_Slash::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	
}
