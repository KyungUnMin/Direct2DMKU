#include "PrecompileHeader.h"
#include "TigerManState_Damaged_Dazed.h"


#include "TigerManFSM.h"

const std::string_view TigerManState_Damaged_Dazed::AniName = "Dazed";
const std::string_view TigerManState_Damaged_Dazed::AniFileName = "TigerMan_Dazed.png";
const std::pair<int, int> TigerManState_Damaged_Dazed::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> TigerManState_Damaged_Dazed::AniFrameIndex = std::pair<size_t, size_t>{ 0, 3 };
const float TigerManState_Damaged_Dazed::AniInterTime = 0.15f;

TigerManState_Damaged_Dazed::TigerManState_Damaged_Dazed()
{

}

TigerManState_Damaged_Dazed::~TigerManState_Damaged_Dazed()
{

}



void TigerManState_Damaged_Dazed::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();
}


void TigerManState_Damaged_Dazed::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_Damaged_Dazed::CreateAnimation()
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


void TigerManState_Damaged_Dazed::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void TigerManState_Damaged_Dazed::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(TigerManStateType::Idle);
}