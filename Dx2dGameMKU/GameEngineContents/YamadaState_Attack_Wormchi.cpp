#include "PrecompileHeader.h"
#include "YamadaState_Attack_Wormchi.h"

#include "FieldCamController.h"

#include "YamadaFSM.h"
#include "AfterImageEffect.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"

const std::string_view YamadaState_Attack_Wormchi::AniFileName = "Yamada_Wormchi.png";
const std::vector<std::string_view> YamadaState_Attack_Wormchi::AniNames =
{
	"Worrmchi_SitDown",
	"Worrmchi_Sit",
	"Worrmchi_GetUp"
};

const std::pair<int, int> YamadaState_Attack_Wormchi::AniCurFrame = std::pair<int, int>(5, 3);
const float YamadaState_Attack_Wormchi::AniInterTime = 0.08f;
const float YamadaState_Attack_Wormchi::SitDuration = 5.f;

YamadaState_Attack_Wormchi::YamadaState_Attack_Wormchi()
{

}

YamadaState_Attack_Wormchi::~YamadaState_Attack_Wormchi()
{

}

void YamadaState_Attack_Wormchi::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	//EnemyStateBase::SetUnbeatable();
}

void YamadaState_Attack_Wormchi::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCurFrame.first, AniCurFrame.second);
}

void YamadaState_Attack_Wormchi::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	std::vector<float> AniFrmTimes(5);
	for (size_t i = 0; i <= 4; ++i)
	{
		AniFrmTimes[i] = AniInterTime;
	}
	AniFrmTimes[3] = 0.2f;

	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::SitDown)],
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 4,
		.Loop = false,
		.FrameTime = AniFrmTimes
	});

	Render->SetAnimationStartEvent(AniNames[static_cast<size_t>(State::SitDown)], 4, []()
	{
		FieldCamController& CamCtrl = FieldLevelBase::GetPtr()->GetCameraController();
		CamCtrl.SetZoom(0.95f);
		CamCtrl.SetZoom(CamCtrl.ZoomOrigin, YamadaState_Attack_Wormchi::SitDuration);
		CamCtrl.SetShakeState(YamadaState_Attack_Wormchi::SitDuration, 3.f);
	});



	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::Sit)],
		.SpriteName = AniFileName,
		.Start = 5,
		.End = 9,
		.FrameInter = AniInterTime,
		.Loop = true
	});

	Render->CreateAnimation
	({
		.AnimationName = AniNames[static_cast<size_t>(State::GetUp)],
		.SpriteName = AniFileName,
		.Start = 10,
		.End = 12,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}


void YamadaState_Attack_Wormchi::EnterState()
{
	BossState_AttackBase::EnterState();
	ChangeStateAndAni(State::SitDown);
}


void YamadaState_Attack_Wormchi::ChangeStateAndAni(State _Next)
{
	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniNames[Index]);
}


void YamadaState_Attack_Wormchi::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaState_Attack_Wormchi::State::SitDown:
		Update_SitDown(_DeltaTime);
		break;
	case YamadaState_Attack_Wormchi::State::Sit:
		Update_Sit(_DeltaTime);
		break;
	case YamadaState_Attack_Wormchi::State::GetUp:
		Update_GetUp(_DeltaTime);
		break;
	}
}

void YamadaState_Attack_Wormchi::Update_SitDown(float _DeltaTime)
{
	AfterEffectTimer += _DeltaTime;
	if (AfterEffectTime < AfterEffectTimer)
	{
		AfterEffectTimer = 0.f;

		std::shared_ptr<AfterImageEffect> Effect = nullptr;
		Effect = CreateEffect<AfterImageEffect>();
		Effect->Init(GetRenderer());
		Effect->SetPlusColor(float4::Green);
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	SitTime = GetLiveTime();
	ChangeStateAndAni(State::Sit);
}

void YamadaState_Attack_Wormchi::Update_Sit(float _DeltaTime)
{
	float Time = GetLiveTime() - SitTime;
	if (Time < SitDuration)
		return;

	ChangeStateAndAni(State::GetUp);
}

void YamadaState_Attack_Wormchi::Update_GetUp(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::Idle);
}





void YamadaState_Attack_Wormchi::ExitState()
{
	BossState_AttackBase::ExitState();
	CurState = State::SitDown;
	FieldLevelBase::GetPtr()->GetCameraController().SetShakeState(0.f);
}