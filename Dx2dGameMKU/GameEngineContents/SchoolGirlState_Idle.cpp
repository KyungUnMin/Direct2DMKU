#include "PrecompileHeader.h"
#include "SchoolGirlState_Idle.h"


#include "SchoolGirlFSM.h"

const std::string_view SchoolGirlState_Idle::AniName = "Idle";
const std::string_view SchoolGirlState_Idle::AniFileName = "SchoolGirl_Idle.png";
const std::pair<int, int> SchoolGirlState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Idle::AniInterTime = 0.08f;

SchoolGirlState_Idle::SchoolGirlState_Idle()
{

}

SchoolGirlState_Idle::~SchoolGirlState_Idle()
{

}

void SchoolGirlState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolGirlState_Idle::LoadAnimation()
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

void SchoolGirlState_Idle::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}


void SchoolGirlState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolGirlState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//공격 상태로 바꾸거나 Idle을 유지하는 경우
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;

	//Idle 대기시간이 끝났을때만 이동상태로 변경
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Walk);
}



