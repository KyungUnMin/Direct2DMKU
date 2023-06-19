#include "PrecompileHeader.h"
#include "NoiseState_Attack_AxeGrind.h"

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "NoiseAxe.h"
#include "FieldEnemyBase.h"

const std::string_view NoiseState_Attack_AxeGrind::Idle_AniFileName = "Noise_AxeGrind_Idle.png";
const std::string_view NoiseState_Attack_AxeGrind::Catch_AniFileName = "Noise_AxeGrind_Catch.png";
const float NoiseState_Attack_AxeGrind::AniInterTime = 0.08f;


const float NoiseState_Attack_AxeGrind::AxeMoveDuration = 0.25f;
const float NoiseState_Attack_AxeGrind::AxeStayDuration = 0.5f;


NoiseState_Attack_AxeGrind::NoiseState_Attack_AxeGrind()
{

}

NoiseState_Attack_AxeGrind::~NoiseState_Attack_AxeGrind()
{

}

void NoiseState_Attack_AxeGrind::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetUnbeatable();
}

void NoiseState_Attack_AxeGrind::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Attack");
	Dir.Move("AxeGrind");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Idle_AniFileName).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Catch_AniFileName).GetFullPath(), 5, 1);
}

void NoiseState_Attack_AxeGrind::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = Idle_AniFileName,
		.SpriteName = Idle_AniFileName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	Render->CreateAnimation
	({
		.AnimationName = Catch_AniFileName,
		.SpriteName = Catch_AniFileName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}


void NoiseState_Attack_AxeGrind::EnterState()
{
	BossState_AttackBase::EnterState();

	CurState = State::Idle;
	GetRenderer()->ChangeAnimation(Idle_AniFileName);

	CreateAxe();
}

void NoiseState_Attack_AxeGrind::CreateAxe()
{
	static const float CreateOffset = 50.f;
	static const float AxeMoveOffset = 300.f;
	
	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();
	float4 ThrowDir = IsRightDir() ? float4::Right : float4::Left;

	float4 CreatePos = EnemyPos + (ThrowDir * CreateOffset);
	float4 AxeDest = CreatePos + (ThrowDir * AxeMoveOffset);

	CreateEffect<NoiseAxe>()->Init(EnemyPos, AxeDest, AxeMoveDuration, AxeStayDuration);
}


void NoiseState_Attack_AxeGrind::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_Attack_AxeGrind::State::Idle:
		Update_Idle();
		break;
	case NoiseState_Attack_AxeGrind::State::Catch:
		Update_Catch();
		break;
	}
}

void NoiseState_Attack_AxeGrind::Update_Idle()
{
	if (GetLiveTime() < TotalDuration)
		return;

	CurState = State::Catch;
	GetRenderer()->ChangeAnimation(Catch_AniFileName);
}

void NoiseState_Attack_AxeGrind::Update_Catch() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}