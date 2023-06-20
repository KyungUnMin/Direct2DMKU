#include "PrecompileHeader.h"
#include "NoiseState_Attack_AxeDash.h"

#include "DataMgr.h"

#include "NoiseFSM.h"
#include "NoiseAxe.h"
#include "FieldEnemyBase.h"

//const std::vector<std::string_view> NoiseState_Attack_AxeDash::AniFileNames =
//{
//	"Noise_AxeDashStart.png",
//	"Noise_AxeDashLoop.png",
//	"Noise_AxeDashLand.png",
//};

//const float NoiseState_Attack_AxeDash::AniInterTime = 0.08f;


//const float NoiseState_Attack_AxeDash::AxeMoveDuration = 0.25f;
//const float NoiseState_Attack_AxeDash::AxeStayDuration = 0.5f;


NoiseState_Attack_AxeDash::NoiseState_Attack_AxeDash()
{

}

NoiseState_Attack_AxeDash::~NoiseState_Attack_AxeDash()
{

}

void NoiseState_Attack_AxeDash::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetUnbeatable();
}

void NoiseState_Attack_AxeDash::LoadAnimation()
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
	//GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Idle_AniFileName).GetFullPath(), 5, 1);
	//GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Catch_AniFileName).GetFullPath(), 5, 1);
}

void NoiseState_Attack_AxeDash::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	/*Render->CreateAnimation
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
		});*/
}


void NoiseState_Attack_AxeDash::EnterState()
{
	BossState_AttackBase::EnterState();

	/*CurState = State::Idle;
	GetRenderer()->ChangeAnimation(Idle_AniFileName);*/

	CreateAxe();
}

void NoiseState_Attack_AxeDash::CreateAxe()
{
	static const float CreateOffset = 50.f;
	static const float AxeMoveOffset = 300.f;

	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();
	float4 ThrowDir = IsRightDir() ? float4::Right : float4::Left;

	float4 CreatePos = EnemyPos + (ThrowDir * CreateOffset);
	float4 AxeDest = CreatePos + (ThrowDir * AxeMoveOffset);

	//CreateEffect<NoiseAxe>()->Init(EnemyPos, AxeDest, AxeMoveDuration, AxeStayDuration);
}


void NoiseState_Attack_AxeDash::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);


}
