#include "PrecompileHeader.h"
#include "YamadaState_Defeat.h"


#include "YamadaFSM.h"

#include "FieldEnemyBase.h"

const std::string_view YamadaState_Defeat::Sink_AniName = "Defeat_Sink";
const std::string_view YamadaState_Defeat::Shudder_AniName = "Defeat_Shudder";
const std::string_view YamadaState_Defeat::AniFileName = "Yamada_Defeated.png";
const std::pair<int, int> YamadaState_Defeat::AniCutFrame = std::pair<int, int>(5, 3);
const float YamadaState_Defeat::AniInterTime = 0.08f;

YamadaState_Defeat::YamadaState_Defeat()
{

}

YamadaState_Defeat::~YamadaState_Defeat()
{

}

void YamadaState_Defeat::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Defeat::LoadAnimation()
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
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Defeat::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = Sink_AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->CreateAnimation
	({
		.AnimationName = Shudder_AniName,
		.SpriteName = AniFileName,
		.Start = 9,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = true,
	});
}


void YamadaState_Defeat::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(Sink_AniName);
	EnemyStateBase::OffMainCollider();
}


void YamadaState_Defeat::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (true == IsCrying || false == Render->IsAnimationEnd())
		return;

	Render->ChangeAnimation(Shudder_AniName);
	IsCrying = true;
}



