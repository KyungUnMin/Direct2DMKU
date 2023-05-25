#include "PrecompileHeader.h"
#include "SchoolGirlState_Walk.h"

#include "SchoolGirlFSM.h"

const std::string_view SchoolGirlState_Walk::AniName = "Walk";
const std::string_view SchoolGirlState_Walk::AniFileName = "SchoolGirl_Walk.png";
const std::pair<int, int> SchoolGirlState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float SchoolGirlState_Walk::AniInterTime = 0.08f;

SchoolGirlState_Walk::SchoolGirlState_Walk()
{

}

SchoolGirlState_Walk::~SchoolGirlState_Walk()
{

}


void SchoolGirlState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(SchoolGirlStateType::Idle);
}

void SchoolGirlState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolGirl");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolGirlState_Walk::CreateAnimation()
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


void SchoolGirlState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}

