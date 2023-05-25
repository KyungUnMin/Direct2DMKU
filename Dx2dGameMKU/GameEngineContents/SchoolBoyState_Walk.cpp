#include "PrecompileHeader.h"
#include "SchoolBoyState_Walk.h"

#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Walk::AniName = "Walk";
const std::string_view SchoolBoyState_Walk::AniFileName = "SchoolBoy_Walk.png";
const std::pair<int, int> SchoolBoyState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float SchoolBoyState_Walk::AniInterTime = 0.08f;

SchoolBoyState_Walk::SchoolBoyState_Walk()
{

}

SchoolBoyState_Walk::~SchoolBoyState_Walk()
{

}


void SchoolBoyState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(SchoolBoyStateType::Idle);
}

void SchoolBoyState_Walk::LoadAnimation()
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
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Walk::CreateAnimation()
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


void SchoolBoyState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}

