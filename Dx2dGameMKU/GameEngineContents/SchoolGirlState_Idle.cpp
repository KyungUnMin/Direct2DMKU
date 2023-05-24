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
	EnemyStateBase::Start();

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
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolGirlState_Idle::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();
	if (VecToPlayer.Size() < GetSightRadius())
	{
		SchoolGirlStateType RandomAttack = SchoolGirlFSM::GetRandomAttack();
		GetFSM()->ChangeState(RandomAttack);
	}
	else
	{
		GetFSM()->ChangeState(SchoolGirlStateType::Walk);
	}
}



