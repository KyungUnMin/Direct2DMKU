#include "PrecompileHeader.h"
#include "WaverState_Walk.h"

#include "WaverFSM.h"

const std::string_view WaverState_Walk::AniName = "Walk";
const std::string_view WaverState_Walk::AniFileName = "Waver_Walk.png";
const std::pair<int, int> WaverState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float WaverState_Walk::AniInterTime = 0.08f;

WaverState_Walk::WaverState_Walk()
{

}

WaverState_Walk::~WaverState_Walk()
{

}


void WaverState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(WaverStateType::Idle);
}

void WaverState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void WaverState_Walk::CreateAnimation()
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


void WaverState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

