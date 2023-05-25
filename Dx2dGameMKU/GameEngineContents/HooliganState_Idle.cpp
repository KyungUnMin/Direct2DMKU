#include "PrecompileHeader.h"
#include "HooliganState_Idle.h"


#include "HooliganFSM.h"

const std::string_view HooliganState_Idle::AniName = "Idle";
const std::string_view HooliganState_Idle::AniFileName = "Hooligan_Idle.png";
const std::pair<int, int> HooliganState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float HooliganState_Idle::AniInterTime = 0.08f;

HooliganState_Idle::HooliganState_Idle()
{

}

HooliganState_Idle::~HooliganState_Idle()
{

}

void HooliganState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void HooliganState_Idle::LoadAnimation()
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

void HooliganState_Idle::CreateAnimation() 
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


void HooliganState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void HooliganState_Idle::Update(float _DeltaTime) 
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

	GetFSM()->ChangeState(HooliganStateType::Walk);
	
}



