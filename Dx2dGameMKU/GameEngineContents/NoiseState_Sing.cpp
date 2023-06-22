#include "PrecompileHeader.h"
#include "NoiseState_Sing.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "NoiseFSM.h"
#include "FieldEnemyBase.h"
#include "NoiseFloor.h"
#include "FieldLevelBase.h"
#include "FieldPlayer.h"



const std::string_view NoiseState_Sing::GuitarPlay_FileName = "Noise_GuitarPlay.png";
const std::string_view NoiseState_Sing::GuitarSing_FileName = "Noise_GuitarSing.png";
const std::string_view NoiseState_Sing::FloorLine_FileName = "OceanConcert_Rails.png";

const float NoiseState_Sing::AniInterTime = 0.08f;

const std::vector<float> NoiseState_Sing::Durations = { FLT_MAX, FLT_MAX ,FLT_MAX };
const std::vector<size_t> NoiseState_Sing::SpawnTimeCount = { 5, 4, 3 };

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

	BossFSMBase* FsmPtr = GetConvertFSM<BossFSMBase>();
	CurPhase = FsmPtr->GetCurPhase();
	if (CurPhase % 2)
	{
		GetRenderer()->ChangeAnimation(GuitarSing_FileName);
	}
	else
	{
		GetRenderer()->ChangeAnimation(GuitarPlay_FileName);
	}

	FloorLines->On();
	ChangePlayerColTrans();
}



void NoiseState_Sing::ChangePlayerColTrans()
{
	static const float4 PlayerColScale = float4{ 80.f, 20.f, 20.f };

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	std::shared_ptr<GameEngineCollision> PlayerMainCollider = nullptr;
	GameEngineTransform* PlayerColTrans = nullptr;

	PlayerMainCollider = Player->GetMainCollider();
	PlayerColTrans = PlayerMainCollider->GetTransform();

	PlayerOriginColScale = PlayerColTrans->GetLocalScale();
	PlayerColTrans->SetLocalScale(PlayerColScale);
	PlayerMainCollider->SetColType(ColType::AABBBOX3D);

	Player->GetAttackCollider()->SetColType(ColType::MAX);
}


void NoiseState_Sing::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	Update_Rail();

	if (true == GetRenderer()->IsAnimationEnd())
	{
		static size_t Count = 0;
		++Count;
		if (0 == (Count % SpawnTimeCount[CurPhase]))
		{
			CreateFloor();
			Count = 0;
		}
	}

	if (GetLiveTime() < Durations[CurPhase])
		return;

	//GetFSM()->ChangeState(NoiseStateType::Idle);
}



void NoiseState_Sing::Update_Rail()
{
	static const float Duration = 0.2f;
	float LiveTime = GetLiveTime();

	//현재 페이즈의 노래 시간
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


void NoiseState_Sing::CreateFloor()
{
	static const int FloorMaxCount = 6;
	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();

	//6개의 레일 중에서 어떤 레일에 발판을 생성할 것인지 비트연산자로 표현
	int RandNum = GameEngineRandom::MainRandom.RandomInt(1, (1 << FloorMaxCount) - 1);
	for (int i = 0; i < FloorMaxCount; ++i)
	{
		//i번째 레일에 발판을 생성하는 경우에만
		if (0 == (RandNum & (1 << i)))
			continue;

		std::shared_ptr<NoiseFloor> Floor = nullptr;
		Floor = Level->CreateActor<NoiseFloor>(UpdateOrder::Effect);
		Floor->Init(static_cast<NoiseFloorType>(i), CurPhase);
	}
}


void NoiseState_Sing::ExitState()
{
	EnemyStateBase::ExitState();

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	std::shared_ptr<GameEngineCollision> PlayerMainCollider = nullptr;
	GameEngineTransform* PlayerColTrans = nullptr;

	PlayerMainCollider = Player->GetMainCollider();
	PlayerColTrans = PlayerMainCollider->GetTransform();

	PlayerColTrans->SetLocalScale(PlayerOriginColScale);
	PlayerMainCollider->SetColType(ColType::SPHERE3D);

	Player->GetAttackCollider()->SetColType(ColType::SPHERE3D);
}