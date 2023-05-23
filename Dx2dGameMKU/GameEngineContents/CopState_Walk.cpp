#include "PrecompileHeader.h"
#include "CopState_Walk.h"

#include "CopFSM.h"

const std::string_view CopState_Walk::AniName = "Walk";
const std::string_view CopState_Walk::AniFileName = "Cop_Walk.png";
const std::pair<int, int> CopState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float CopState_Walk::AniInterTime = 0.08f;

CopState_Walk::CopState_Walk()
{

}

CopState_Walk::~CopState_Walk()
{

}


void CopState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyState_WalkBase::SetNextState(CopStateType::Idle);
}

void CopState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cop");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CopState_Walk::CreateAnimation()
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


void CopState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}

