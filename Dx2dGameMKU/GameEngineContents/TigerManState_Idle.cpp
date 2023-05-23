#include "PrecompileHeader.h"
#include "TigerManState_Idle.h"


#include "TigerManFSM.h"

const std::string_view TigerManState_Idle::AniName = "Idle";
const std::string_view TigerManState_Idle::AniFileName = "TigerMan_Idle.png";
const std::pair<int, int> TigerManState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float TigerManState_Idle::AniInterTime = 0.08f;

TigerManState_Idle::TigerManState_Idle()
{

}

TigerManState_Idle::~TigerManState_Idle()
{

}

void TigerManState_Idle::Start() 
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void TigerManState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void TigerManState_Idle::CreateAnimation() 
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


void TigerManState_Idle::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void TigerManState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		TigerManStateType RandomAttack = TigerManFSM::GetRandomAttack();
		GetFSM()->ChangeState(RandomAttack);
	}
	else
	{
		GetFSM()->ChangeState(TigerManStateType::Walk);
	}
}



