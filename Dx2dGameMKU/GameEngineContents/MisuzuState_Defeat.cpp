#include "PrecompileHeader.h"
#include "MisuzuState_Defeat.h"


#include "MisuzuFSM.h"

#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Defeat::Sink_AniName = "Defeat_Sink";
const std::string_view MisuzuState_Defeat::Cry_AniName = "Defeat_Cry";
const std::string_view MisuzuState_Defeat::AniFileName = "Misuzu_Defeat.png";
const std::pair<int, int> MisuzuState_Defeat::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Defeat::AniInterTime = 0.08f;

MisuzuState_Defeat::MisuzuState_Defeat()
{

}

MisuzuState_Defeat::~MisuzuState_Defeat()
{

}

void MisuzuState_Defeat::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Defeat::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Defeat::CreateAnimation()
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


void MisuzuState_Defeat::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(Sink_AniName);
	EnemyStateBase::OffMainCollider();
}


void MisuzuState_Defeat::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (true == IsCrying || false == Render->IsAnimationEnd())
		return;

	Render->ChangeAnimation(Cry_AniName);
	IsCrying = true;
}



