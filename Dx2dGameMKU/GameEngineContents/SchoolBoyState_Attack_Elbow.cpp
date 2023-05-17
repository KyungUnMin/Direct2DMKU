#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_Elbow.h"


#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view SchoolBoyState_Attack_Elbow::AniFileName = "SchoolBoy_Elbow_Uppercut.png";
const std::pair<int, int> SchoolBoyState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_Elbow::AniInterTime = 0.08f;

SchoolBoyState_Attack_Elbow::SchoolBoyState_Attack_Elbow()
{

}

SchoolBoyState_Attack_Elbow::~SchoolBoyState_Attack_Elbow()
{

}

void SchoolBoyState_Attack_Elbow::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_Elbow::LoadAnimation()
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

void SchoolBoyState_Attack_Elbow::CreateAnimation()
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


void SchoolBoyState_Attack_Elbow::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Attack_Elbow::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Punch);

	//TODO
	//GetRenderer()
}



