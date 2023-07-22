#include "PrecompileHeader.h"
#include "WaverState_Attack_DiceSpike.h"

#include "WaverFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view WaverState_Attack_DiceSpike::AniName = "Attack_DiceSpike";
const std::string_view WaverState_Attack_DiceSpike::AniFileName = "Waver_DiceSpike.png";
const std::pair<int, int> WaverState_Attack_DiceSpike::AniCutFrame = std::pair<int, int>(5, 3);
const float WaverState_Attack_DiceSpike::AniInterTime = 0.06f;
const int WaverState_Attack_DiceSpike::Damage = 8;

WaverState_Attack_DiceSpike::WaverState_Attack_DiceSpike()
{

}

WaverState_Attack_DiceSpike::~WaverState_Attack_DiceSpike()
{

}

void WaverState_Attack_DiceSpike::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_DiceSpike::LoadAnimation()
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

void WaverState_Attack_DiceSpike::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 13,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 4);
}




void WaverState_Attack_DiceSpike::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void WaverState_Attack_DiceSpike::Update(float _DeltaTime)
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


void WaverState_Attack_DiceSpike::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	
}
