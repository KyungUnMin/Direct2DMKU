#include "PrecompileHeader.h"
#include "CheerleaderState_CartWheel.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "CheerleaderFSM.h"
#include "AfterImageEffect.h"
#include "FieldLevelBase.h"
#include "FieldEnemyBase.h"


const std::string_view CheerleaderState_CartWheel::AniName = "CartWheel";
const std::string_view CheerleaderState_CartWheel::AniFileName = "Cheerleader_CartWheel.png";
const std::pair<int, int> CheerleaderState_CartWheel::AniCutFrame = std::pair<int, int>(5, 3);
const float CheerleaderState_CartWheel::AniInterTime = 0.05f;
const float CheerleaderState_CartWheel::Duration = 0.5f;
const float CheerleaderState_CartWheel::StartMoveAcc = 1000.f;

CheerleaderState_CartWheel::CheerleaderState_CartWheel()
{

}

CheerleaderState_CartWheel::~CheerleaderState_CartWheel()
{

}

void CheerleaderState_CartWheel::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyMainCollider = GetEnemy()->GetMainCollider();
}

void CheerleaderState_CartWheel::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_CartWheel::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});

	Render->SetAnimationStartEvent(AniName, 4, [this]
	{
		this->MoveOn();
	});
}


void CheerleaderState_CartWheel::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	MoveDir = EnemyStateBase::IsRightDir() ? float4::Right : float4::Left;
	MoveOnValue = false;
	EffectTimer = 0.f;

	EnemyMainCollider->Off();
}



void CheerleaderState_CartWheel::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == MoveOnValue)
		return;
	
	float Time = GetLiveTime() - MoveStartTime;
	float Ratio = (Time / Duration);
	EnemyStateBase::Update_AccMove(_DeltaTime, Ratio, MoveDir, StartMoveAcc);


	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	EffectTimer += _DeltaTime;
	if (EffectCreateTime < EffectTimer)
	{
		EffectTimer -= EffectCreateTime;
		std::shared_ptr<AfterImageEffect> Effect = FieldLevelBase::GetPtr()->CreateActor<AfterImageEffect>(UpdateOrder::Effect);
		Effect->Init(Render);
	}


	if (false == Render->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CheerleaderStateType::Idle);
}


void CheerleaderState_CartWheel::ExitState()
{
	EnemyStateBase::ExitState();
	EnemyMainCollider->On();
}
