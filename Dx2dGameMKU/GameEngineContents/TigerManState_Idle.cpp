#include "PrecompileHeader.h"
#include "TigerManState_Idle.h"

#include <GameEngineBase/GameEngineRandom.h>

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
	EnemyState_IdleBase::Start();

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
		.FrameInter = AniInterTime
	});
}


void TigerManState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void TigerManState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//인자로 들어간 확률로 Rolling 공격을 시도한다
	if (true == RollingExcute(10))
		return;

	
	//공격 상태로 바꾸거나 Idle을 유지하는 경우
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle 대기시간이 끝났을때만 이동상태로 변경
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;

	GetFSM()->ChangeState(TigerManStateType::Walk);
}

bool TigerManState_Idle::RollingExcute(int _Percent)
{
	//누군가가 공격중이라면 무조건 Rolling 스킬 발동하지 않는다
	if (false == EnemyState_IdleBase::IsAttackerEmpty())
		return false;


	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (_Percent < RandValue)
		return false;

	GetFSM()->ChangeState(TigerManStateType::Rolling);
	return true;
}

