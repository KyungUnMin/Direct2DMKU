#include "PrecompileHeader.h"
#include "NoiseState_Defeat.h"


#include "NoiseFSM.h"

#include "FieldEnemyBase.h"

const std::string_view NoiseState_Defeat::Sink_AniName = "Defeat_Sink";
const std::string_view NoiseState_Defeat::Cry_AniName = "Defeat_Cry";
const std::string_view NoiseState_Defeat::AniFileName = "Noise_Defeat.png";
const std::pair<int, int> NoiseState_Defeat::AniCutFrame = std::pair<int, int>(5, 3);
const float NoiseState_Defeat::AniInterTime = 0.08f;

NoiseState_Defeat::NoiseState_Defeat()
{

}

NoiseState_Defeat::~NoiseState_Defeat()
{

}

void NoiseState_Defeat::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Defeat::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Defeat::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = Sink_AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->CreateAnimation
	({
		.AnimationName = Cry_AniName,
		.SpriteName = AniFileName,
		.Start = 9,
		.End = 11,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
}


void NoiseState_Defeat::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(Sink_AniName);
	EnemyStateBase::OffMainCollider();
}


void NoiseState_Defeat::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (true == IsCrying || false == Render->IsAnimationEnd())
		return;

	Render->ChangeAnimation(Cry_AniName);
	IsCrying = true;
}



