#include "PrecompileHeader.h"
#include "CheerleaderState_Idle.h"


#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_Idle::AniName = "Idle";
const std::string_view CheerleaderState_Idle::AniFileName = "Cheerleader_Idle.png";
const std::pair<int, int> CheerleaderState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float CheerleaderState_Idle::AniInterTime = 0.08f;

CheerleaderState_Idle::CheerleaderState_Idle()
{

}

CheerleaderState_Idle::~CheerleaderState_Idle()
{

}

void CheerleaderState_Idle::Start() 
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Idle::CreateAnimation() 
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


void CheerleaderState_Idle::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void CheerleaderState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		CheerleaderStateType RandomAttack = CheerleaderFSM::GetRandomAttack();
		GetFSM()->ChangeState(RandomAttack);
	}
	else
	{
		GetFSM()->ChangeState(CheerleaderStateType::Walk);
	}
}



