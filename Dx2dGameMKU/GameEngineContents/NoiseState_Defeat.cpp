#include "PrecompileHeader.h"
#include "NoiseState_Defeat.h"


#include "NoiseFSM.h"

#include "FieldEnemyBase.h"

const std::string_view NoiseState_Defeat::AniFileName = "Noise_Defeat.png";
const std::string_view NoiseState_Defeat::AniName = "Defeat";
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

	EnemyStateBase::DontLookPlayer();
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 5, 3);
}


void NoiseState_Defeat::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 3,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
}


void NoiseState_Defeat::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyStateBase::OffMainCollider();
}


void NoiseState_Defeat::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	
}



