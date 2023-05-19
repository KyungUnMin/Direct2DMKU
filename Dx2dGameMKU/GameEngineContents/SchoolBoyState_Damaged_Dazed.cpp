#include "PrecompileHeader.h"
#include "SchoolBoyState_Damaged_Dazed.h"

#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Damaged_Dazed::AniName = "Dazed";
const std::string_view SchoolBoyState_Damaged_Dazed::AniFileName = "SchoolBoy_Dazed.png";
const std::pair<int, int> SchoolBoyState_Damaged_Dazed::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> SchoolBoyState_Damaged_Dazed::AniFrameIndex = std::pair<size_t, size_t>{ 0, 3 };
const float SchoolBoyState_Damaged_Dazed::AniInterTime = 0.1f;

SchoolBoyState_Damaged_Dazed::SchoolBoyState_Damaged_Dazed()
{

}

SchoolBoyState_Damaged_Dazed::~SchoolBoyState_Damaged_Dazed()
{

}



void SchoolBoyState_Damaged_Dazed::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();
}


void SchoolBoyState_Damaged_Dazed::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Damaged_Dazed::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime,
	});

}


void SchoolBoyState_Damaged_Dazed::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void SchoolBoyState_Damaged_Dazed::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Idle);
}