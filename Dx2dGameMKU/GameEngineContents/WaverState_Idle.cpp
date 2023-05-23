#include "PrecompileHeader.h"
#include "WaverState_Idle.h"


#include "WaverFSM.h"

const std::string_view WaverState_Idle::AniName = "Idle";
const std::string_view WaverState_Idle::AniFileName = "Waver_Idle.png";
const std::pair<int, int> WaverState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float WaverState_Idle::AniInterTime = 0.08f;

WaverState_Idle::WaverState_Idle()
{

}

WaverState_Idle::~WaverState_Idle()
{

}

void WaverState_Idle::Start() 
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void WaverState_Idle::CreateAnimation() 
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


void WaverState_Idle::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void WaverState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		WaverStateType RandomAttack = WaverFSM::GetRandomAttack();
		GetFSM()->ChangeState(RandomAttack);
	}
	else
	{
		GetFSM()->ChangeState(WaverStateType::Walk);
	}
}



