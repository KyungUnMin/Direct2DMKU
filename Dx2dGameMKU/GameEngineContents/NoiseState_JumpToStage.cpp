#include "PrecompileHeader.h"
#include "NoiseState_JumpToStage.h"

#include "SoundMgr.h"

#include "NoiseFSM.h"

#include "FieldEnemyBase.h"
#include "FieldCamController.h"
#include "FieldLevelBase.h"

const std::vector<std::string_view> NoiseState_JumpToStage::AniFileNames =
{
	"Noise_JumpToStage1.png",
	"Noise_JumpToStage2.png",
	"Noise_LandStage1.png",
	"Noise_LandStage2.png",
};

const float NoiseState_JumpToStage::AniInterTime = 0.08f;

const std::vector<std::string_view> NoiseState_JumpToStage::SfxVoice =
{
	"Noise_JumpToStage_Voice0.wav",
	"Noise_JumpToStage_Voice1.wav",
	"Noise_JumpToStage_Voice2.wav",
};

NoiseState_JumpToStage::NoiseState_JumpToStage()
{

}

NoiseState_JumpToStage::~NoiseState_JumpToStage()
{

}

void NoiseState_JumpToStage::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetUnbeatable();

	Shadow = GetEnemy()->GetShadowRender();
	BossFsmPtr = GetConvertFSM<BossFSMBase>();
	if (nullptr == BossFsmPtr)
	{
		MsgAssert("현재 State가 보스의 FSM에 속해있지 않습니다");
		return;
	}
}

void NoiseState_JumpToStage::LoadAnimation()
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
	Dir.Move("Movement");
	Dir.Move("JumpToStage");

	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Ready)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Jump)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Fall)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Land)]).GetFullPath(), 5, 2);
}

void NoiseState_JumpToStage::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	std::string_view AniName = "";

	AniName = AniFileNames[static_cast<size_t>(State::Ready)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	AniName = AniFileNames[static_cast<size_t>(State::Jump)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 2,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	AniName = AniFileNames[static_cast<size_t>(State::Fall)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 3,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	AniName = AniFileNames[static_cast<size_t>(State::Land)];
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = 7,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}







void NoiseState_JumpToStage::EnterState()
{
	EnemyStateBase::EnterState();

	ChangeStateAndAni(State::Ready);
	PlaySfx();
}



void NoiseState_JumpToStage::ChangeStateAndAni(State _Next)
{
	ResetLiveTime();

	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	const std::string_view& AniName = AniFileNames[Index];
	GetRenderer()->ChangeAnimation(AniName);
}


void NoiseState_JumpToStage::PlaySfx()
{
	SoundMgr::BgmStop();
	size_t CurPhase = BossFsmPtr->GetCurPhase();
	if (SfxVoice.size() <= CurPhase)
	{
		MsgAssert("페이즈 계산이 잘못되었습니다\n현재 페이즈 : " + GameEngineString::ToString(CurPhase));
		return;
	}

	GameEngineSoundPlayer SoundPlayer = SoundMgr::PlaySFX(SfxVoice[CurPhase]);
	if (0 == CurPhase)
		return;
	
	SfxPlayer = SoundPlayer;
}


void NoiseState_JumpToStage::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_JumpToStage::State::Ready:
		Update_Ready(_DeltaTime);
		break;
	case NoiseState_JumpToStage::State::Jump:
		Update_Jump(_DeltaTime);
		break;
	case NoiseState_JumpToStage::State::Fall:
		Update_Fall(_DeltaTime);
		break;
	case NoiseState_JumpToStage::State::Land:
		Update_Land(_DeltaTime);
		break;
	}
}




void NoiseState_JumpToStage::Update_Ready(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	ChangeStateAndAni(State::Jump);
}


void NoiseState_JumpToStage::Update_Jump(float _DeltaTime) 
{
	static const float Duration = 0.5f;
	static const float MaxHeight = 1000.f;

	EnemyStateBase::Update_SinHalfJump(Duration, MaxHeight);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	Shadow->ColorOptionValue.MulColor.a = (1.f - ClampRatio);

	if (Ratio < 1.f)
		return;

	const float4 StagePosition = { 0.f, 60.f, 60.f };
	const float4 CamFocus = { 0.f, -100.f, 0.f };
	const float CamZoomRatio = 1.2f;

	//위치 조정
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	EnemyTrans->SetLocalPosition(StagePosition);

	//카메라 조정
	FieldCamController& CamCtrl = FieldLevelBase::GetPtr()->GetCameraController();
	CamCtrl.SetFixedState(CamFocus);
	FieldCamController::ZoomOrigin = CamZoomRatio;
	CamCtrl.SetZoom(FieldCamController::ZoomOrigin, 1.f);

	ChangeStateAndAni(State::Fall);
}


void NoiseState_JumpToStage::Update_Fall(float _DeltaTime)
{
	static const float Duration = 0.5f;
	static const float MaxHeight = 1000.f;

	EnemyStateBase::Update_SinHalfFall(Duration, MaxHeight);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	Shadow->ColorOptionValue.MulColor.a = ClampRatio;

	if (Ratio < 1.f)
		return;

	ChangeStateAndAni(State::Land);
}


void NoiseState_JumpToStage::Update_Land(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Sing);
}


void NoiseState_JumpToStage::ExitState()
{
	EnemyStateBase::ExitState();

	if (false == SfxPlayer.IsValid())
		return;

	bool IsSfxPlay = true;
	SfxPlayer.isPlaying(&IsSfxPlay);
	if (true == IsSfxPlay)
	{
		SfxPlayer.SoundFadeOut(1.f, 0.f, true);
	}
}