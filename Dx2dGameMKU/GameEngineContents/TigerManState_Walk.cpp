#include "PrecompileHeader.h"
#include "TigerManState_Walk.h"

#include "TigerManFSM.h"

const std::string_view TigerManState_Walk::AniName = "Walk";
const std::string_view TigerManState_Walk::AniFileName = "TigerMan_Walk.png";
const std::pair<int, int> TigerManState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float TigerManState_Walk::AniInterTime = 0.08f;

TigerManState_Walk::TigerManState_Walk()
{

}

TigerManState_Walk::~TigerManState_Walk()
{

}


void TigerManState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(TigerManStateType::Idle);
}

void TigerManState_Walk::LoadAnimation()
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
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_Walk::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime
	});
}


void TigerManState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

