#include "PrecompileHeader.h"
#include "WaverState_Attack_DoubleSlash.h"

#include "DataMgr.h"

#include "WaverFSM.h"
#include "FieldPlayer.h"

const std::string_view WaverState_Attack_DoubleSlash::AniName = "Attack_DoubleSlash";
const std::string_view WaverState_Attack_DoubleSlash::AniFileName = "Waver_DoubleSlash.png";
const std::pair<int, int> WaverState_Attack_DoubleSlash::AniCutFrame = std::pair<int, int>(5, 2);
const float WaverState_Attack_DoubleSlash::AniInterTime = 0.08f;
const int WaverState_Attack_DoubleSlash::Damage = 5;

WaverState_Attack_DoubleSlash::WaverState_Attack_DoubleSlash()
{

}

WaverState_Attack_DoubleSlash::~WaverState_Attack_DoubleSlash()
{

}

void WaverState_Attack_DoubleSlash::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_DoubleSlash::LoadAnimation()
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

void WaverState_Attack_DoubleSlash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	size_t AniFrmCnt = static_cast<size_t>(AniCutFrame.first * AniCutFrame.second);
	std::vector<float> AniInters(AniFrmCnt, AniInterTime);
	AniInters[0] = 0.1f;
	AniInters[1] = 0.1f;
	AniInters[2] = 0.2f;

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Loop = false,
		.FrameTime = AniInters,
	});



	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}


void WaverState_Attack_DoubleSlash::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void WaverState_Attack_DoubleSlash::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	EnemyStateBase::Update_SinJump(JumpDuration, JumpMaxHeight);

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



void WaverState_Attack_DoubleSlash::Attack()
{
	EnemyState_AttackBase::Attack();
	bool Result = FieldPlayer::GetPtr()->OnDamage_Jaw(Damage);
	

}
