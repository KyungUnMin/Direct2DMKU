#include "PrecompileHeader.h"
#include "WaverState_Attack_WindSlash.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "WaverFSM.h"
#include "FieldPlayer.h"

const std::string_view WaverState_Attack_WindSlash::AniName = "Attack_WindSlash";
const std::string_view WaverState_Attack_WindSlash::AniFileName = "Waver_WindSlash.png";
const std::pair<int, int> WaverState_Attack_WindSlash::AniCutFrame = std::pair<int, int>(5, 5);
const float WaverState_Attack_WindSlash::AniInterTime = 0.08f;
const int WaverState_Attack_WindSlash::Damage = 30;

WaverState_Attack_WindSlash::WaverState_Attack_WindSlash()
{

}

WaverState_Attack_WindSlash::~WaverState_Attack_WindSlash()
{

}

void WaverState_Attack_WindSlash::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_WindSlash::LoadAnimation()
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

void WaverState_Attack_WindSlash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 23,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(AniName, 8, [this]()
	{
		SfxPlayer = SoundMgr::PlaySFX("Waver_WindSlash_Wind.wav", true);
	});

	Render->SetAnimationStartEvent(AniName, 16, [this]()
	{
		if (true == SfxPlayer.IsValid())
		{
			SfxPlayer.Stop();
		}
		SoundMgr::PlaySFX("Waver_WindSlash_Attack.wav");
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 17);
}


void WaverState_Attack_WindSlash::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void WaverState_Attack_WindSlash::Update(float _DeltaTime)
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




void WaverState_Attack_WindSlash::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(Damage);
	
}


void WaverState_Attack_WindSlash::ExitState()
{
	EnemyState_AttackBase::ExitState();

	if (true == SfxPlayer.IsValid())
	{
		SfxPlayer.Stop();
	}
}