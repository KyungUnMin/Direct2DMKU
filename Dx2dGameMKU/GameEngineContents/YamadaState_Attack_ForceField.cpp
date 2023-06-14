#include "PrecompileHeader.h"
#include "YamadaState_Attack_ForceField.h"

#include "RCGEnums.h"

#include "YamadaFSM.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "YamadaEnergyBallCtrl.h"



const std::vector<std::string_view> YamadaState_Attack_ForceField::AniNames =
{
	"Attack_ForceField_Ready",
	"Attack_ForceField_Rise",
	"Attack_ForceField_Hang Is Unused",
	"Attack_ForceField_Land",
	"Attack_ForceField_Spread",
};
const std::string_view YamadaState_Attack_ForceField::AniFileName = "Yamada_ForceField.png";
const std::pair<int, int> YamadaState_Attack_ForceField::AniCutFrame = std::pair<int, int>(5, 5);
const float YamadaState_Attack_ForceField::AniInterTime = 0.08f;

YamadaState_Attack_ForceField::YamadaState_Attack_ForceField()
{

}

YamadaState_Attack_ForceField::~YamadaState_Attack_ForceField()
{

}

void YamadaState_Attack_ForceField::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	//EnemyStateBase::DontLookPlayer();
}

void YamadaState_Attack_ForceField::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Attack_ForceField::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Ready)],
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Rise)],
		.SpriteName = AniFileName,
		.Start = 7,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Land)],
		.SpriteName = AniFileName,
		.Start = 11,
		.End = 13,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Spread)],
		.SpriteName = AniFileName,
		.Start = 14,
		.End = 23,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}





void YamadaState_Attack_ForceField::EnterState()
{
	BossState_AttackBase::EnterState();

	ChangeStateAndAni(State::Ready);
}



void YamadaState_Attack_ForceField::ChangeStateAndAni(State _NextState)
{
	CurState = _NextState;

	if (State::Hang != _NextState)
	{
		size_t Index = static_cast<size_t>(CurState);
		GetRenderer()->ChangeAnimation(AniNames[Index]);
	}

	ResetLiveTime();
}



void YamadaState_Attack_ForceField::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaState_Attack_ForceField::State::Ready:
		Update_Ready(_DeltaTime);
		break;
	case YamadaState_Attack_ForceField::State::Rise:
		Update_Rise(_DeltaTime);
		break;
	case YamadaState_Attack_ForceField::State::Hang:
		Update_Hang(_DeltaTime);
		break;
	case YamadaState_Attack_ForceField::State::Land:
		Update_Land(_DeltaTime);
		break;
	case YamadaState_Attack_ForceField::State::Spread:
		Update_Spread(_DeltaTime);
		break;
	}
}



void YamadaState_Attack_ForceField::Update_Ready(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	ChangeStateAndAni(State::Rise);
	EnergyBallCtrl = CreateEffect<YamadaEnergyBallCtrl>();
	EnergyBallCtrl->Init(EtyrtTime + RiseTime);
}

void YamadaState_Attack_ForceField::Update_Rise(float _DeltaTime)
{
	float Ratio = GetLiveTime() / RiseTime;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);
	GetEnemy()->SetHeight(SinValue * MaxHeight);

	if (Ratio < 1.f)
		return;

	ChangeStateAndAni(State::Hang);
}

void YamadaState_Attack_ForceField::Update_Hang(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	if (EtyrtTime < LiveTime)
	{
		GetEnemy()->SetHeight(MaxHeight);
		ChangeStateAndAni(State::Land);
		return;
	}

	float SinValue = sinf(GameEngineMath::PIE2 * LiveTime);
	float NowOffset = (MaxHeight * SinValue);
	GetEnemy()->SetHeight(MaxHeight + NowOffset);
}

void YamadaState_Attack_ForceField::Update_Land(float _DeltaTime)
{
	static const float Duration = AniInterTime * 3.f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float CosValue = cosf(GameEngineMath::PIE * 0.5f * ClampRatio);
	GetEnemy()->SetHeight(CosValue * MaxHeight);

	if (Ratio < 1.f)
		return;

	ChangeStateAndAni(State::Spread);
}


void YamadaState_Attack_ForceField::Update_Spread(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}



void YamadaState_Attack_ForceField::ExitState()
{
	BossState_AttackBase::ExitState();
	GetEnemy()->SetHeight(0.f);

	if (false == EnergyBallCtrl->IsDeath())
	{
		EnergyBallCtrl->Clear();
	}

	EnergyBallCtrl = nullptr;
}