#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_Punch.h"


#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Attack_Punch::AniName = "Attack_Punch";
const std::string_view SchoolBoyState_Attack_Punch::AniFileName = "SchoolBoy_Punch.png";
const std::pair<int, int> SchoolBoyState_Attack_Punch::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_Punch::AniInterTime = 0.08f;

SchoolBoyState_Attack_Punch::SchoolBoyState_Attack_Punch()
{

}

SchoolBoyState_Attack_Punch::~SchoolBoyState_Attack_Punch()
{

}

void SchoolBoyState_Attack_Punch::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_Punch::LoadAnimation()
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

void SchoolBoyState_Attack_Punch::CreateAnimation()
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


void SchoolBoyState_Attack_Punch::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Attack_Punch::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::SideKick);

	//TODO
	//GetRenderer()
}
