#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_SideKick.h"

#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Attack_SideKick::AniName = "Attack_SideKick";
const std::string_view SchoolBoyState_Attack_SideKick::AniFileName = "SchoolBoy_Side_Kick.png";
const std::pair<int, int> SchoolBoyState_Attack_SideKick::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_SideKick::AniInterTime = 0.08f;

SchoolBoyState_Attack_SideKick::SchoolBoyState_Attack_SideKick()
{

}

SchoolBoyState_Attack_SideKick::~SchoolBoyState_Attack_SideKick()
{

}

void SchoolBoyState_Attack_SideKick::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_SideKick::LoadAnimation()
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
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Attack_SideKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime
	});
}


void SchoolBoyState_Attack_SideKick::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Attack_SideKick::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Idle);

	//TODO
	//GetRenderer()
}



