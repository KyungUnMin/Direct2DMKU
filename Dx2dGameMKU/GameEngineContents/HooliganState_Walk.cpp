#include "PrecompileHeader.h"
#include "HooliganState_Walk.h"

#include "HooliganFSM.h"

const std::string_view HooliganState_Walk::AniName = "Walk";
const std::string_view HooliganState_Walk::AniFileName = "Hooligan_Walk.png";
const std::pair<int, int> HooliganState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float HooliganState_Walk::AniInterTime = 0.08f;

HooliganState_Walk::HooliganState_Walk()
{

}

HooliganState_Walk::~HooliganState_Walk()
{

}


void HooliganState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(HooliganStateType::Idle);
}

void HooliganState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Hooligan");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void HooliganState_Walk::CreateAnimation()
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


void HooliganState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

