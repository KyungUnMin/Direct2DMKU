#include "PrecompileHeader.h"
#include "CheerleaderState_Walk.h"

#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_Walk::AniName = "Walk";
const std::string_view CheerleaderState_Walk::AniFileName = "Cheerleader_Walk.png";
const std::pair<int, int> CheerleaderState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float CheerleaderState_Walk::AniInterTime = 0.08f;

CheerleaderState_Walk::CheerleaderState_Walk()
{

}

CheerleaderState_Walk::~CheerleaderState_Walk()
{

}


void CheerleaderState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(CheerleaderStateType::Idle);
}

void CheerleaderState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Walk::CreateAnimation()
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


void CheerleaderState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

