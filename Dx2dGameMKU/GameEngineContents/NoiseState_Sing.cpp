#include "PrecompileHeader.h"
#include "NoiseState_Sing.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGEnums.h"

#include "NoiseFSM.h"
#include "FieldEnemyBase.h"

const std::string_view NoiseState_Sing::GuitarPlay_FileName = "Noise_GuitarPlay.png";
const std::string_view NoiseState_Sing::GuitarSing_FileName = "Noise_GuitarSing.png";
const std::string_view NoiseState_Sing::FloorLine_FileName = "OceanConcert_Rails.png";

const float NoiseState_Sing::AniInterTime = 0.08f;

const std::vector<float> NoiseState_Sing::Durations = { FLT_MAX, FLT_MAX ,FLT_MAX };


NoiseState_Sing::NoiseState_Sing()
{

}

NoiseState_Sing::~NoiseState_Sing()
{

}

void NoiseState_Sing::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	FsmPtr = GetConvertFSM<BossFSMBase>();
	CreateFloorLine();
}

void NoiseState_Sing::LoadAnimation()
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
	Dir.Move("Sing");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(GuitarPlay_FileName).GetFullPath(), 5, 2);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(GuitarSing_FileName).GetFullPath(), 5, 2);
	GameEngineTexture::Load(Dir.GetPlusFileName(FloorLine_FileName).GetFullPath());
}

void NoiseState_Sing::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = GuitarPlay_FileName,
		.SpriteName = GuitarPlay_FileName,
		.Start = 0,
		.End = 5,
		.FrameInter = AniInterTime,
		.Loop = true,
	});

	Render->CreateAnimation
	({
		.AnimationName = GuitarSing_FileName,
		.SpriteName = GuitarSing_FileName,
		.Start = 0,
		.End = 5,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
}


void NoiseState_Sing::CreateFloorLine()
{
	FloorLines = GetEnemy()->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	FloorLines->SetScaleToTexture(FloorLine_FileName);

	GameEngineTransform* FloorTrans = FloorLines->GetTransform();
	FloorTrans->SetLocalScale(FloorTrans->GetLocalScale() * RCGDefine::ResourceScaleConvertor);
	FloorTrans->SetWorldPosition(float4{0.f, -217.f, 450.f});

	FloorLines->ImageClippingY(0.f, ClipYDir::Top);
	FloorLines->Off();
}






void NoiseState_Sing::EnterState()
{
	EnemyStateBase::EnterState();

	if (false == FsmPtr->IsLastPhase())
	{
		GetRenderer()->ChangeAnimation(GuitarPlay_FileName);
	}
	else
	{
		GetRenderer()->ChangeAnimation(GuitarSing_FileName);
	}

	FloorLines->On();
}


void NoiseState_Sing::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	Update_Rail();

	if (true == GetRenderer()->IsAnimationEnd())
	{
		//TODO 생성
	}

	size_t CurPhase = FsmPtr->GetCurPhase();
	if (GetLiveTime() < Durations[CurPhase])
		return;

	//GetFSM()->ChangeState(NoiseStateType::Idle);
}



void NoiseState_Sing::Update_Rail()
{
	static const float Duration = 0.2f;
	float LiveTime = GetLiveTime();

	//현재 페이즈의 노래 시간
	size_t CurPhase = FsmPtr->GetCurPhase();
	const float CurSingDuration = Durations[CurPhase];

	//레일이 회수되는 시간
	const float RecoverTime = (CurSingDuration - Duration);

	float Ratio = 0.f;
	if (LiveTime < Duration)
	{
		Ratio = (LiveTime / Duration);
	}
	else if (RecoverTime < LiveTime)
	{
		Ratio = (LiveTime - RecoverTime) / Duration;
		Ratio = std::clamp(1.f - Ratio, 0.f, 1.f);
	}
	else
	{
		Ratio = 1.f;
	}

	FloorLines->ImageClippingY(Ratio, ClipYDir::Top);
}
