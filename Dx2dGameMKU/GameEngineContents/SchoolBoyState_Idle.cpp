#include "PrecompileHeader.h"
#include "SchoolBoyState_Idle.h"


#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Idle::AniName = "Idle";
const std::string_view SchoolBoyState_Idle::AniFileName = "SchoolBoy_Idle.png";
const std::pair<int, int> SchoolBoyState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Idle::AniInterTime = 0.08f;
const float SchoolBoyState_Idle::SightRadius = 100.f;

SchoolBoyState_Idle::SchoolBoyState_Idle()
{

}

SchoolBoyState_Idle::~SchoolBoyState_Idle()
{

}

void SchoolBoyState_Idle::Start() 
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Idle::LoadAnimation()
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

void SchoolBoyState_Idle::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 7,
		.FrameInter = AniInterTime
	});
}


void SchoolBoyState_Idle::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < SightRadius)
	{
		GetFSM()->ChangeState(SchoolBoyStateType::AxeKick);
	}
	else
	{
		GetFSM()->ChangeState(SchoolBoyStateType::Walk);
	}
}



