#include "PrecompileHeader.h"
#include "TigerManState_Damaged_WallHit.h"

#include "TigerManFSM.h"

const std::string_view TigerManState_Damaged_WallHit::AniName = "WallHit";
const std::string_view TigerManState_Damaged_WallHit::AniFileName = "TigerMan_WallHit.png";
const std::pair<int, int> TigerManState_Damaged_WallHit::AniCutFrame = std::pair<int, int>(5, 1);
const std::pair<size_t, size_t> TigerManState_Damaged_WallHit::AniFrameIndex = std::pair<size_t, size_t>{ 0, 1 };
const float TigerManState_Damaged_WallHit::AniInterTime = 0.025f;

TigerManState_Damaged_WallHit::TigerManState_Damaged_WallHit()
{

}

TigerManState_Damaged_WallHit::~TigerManState_Damaged_WallHit()
{

}



void TigerManState_Damaged_WallHit::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();
}


void TigerManState_Damaged_WallHit::LoadAnimation()
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

void TigerManState_Damaged_WallHit::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = AniFrameIndex.first,
		.End = AniFrameIndex.second,
		.FrameInter = AniInterTime ,
	});

}


void TigerManState_Damaged_WallHit::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void TigerManState_Damaged_WallHit::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(TigerManStateType::Damaged_WallOut);
}