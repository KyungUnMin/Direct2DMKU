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
	EnemyStateBase::Start();

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
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void HooliganState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		HooliganStateType RandomAttack = HooliganFSM::GetRandomAttack();
		GetFSM()->ChangeState(RandomAttack);
	}
	else
	{
		GetFSM()->ChangeState(HooliganStateType::Walk);
	}
}



