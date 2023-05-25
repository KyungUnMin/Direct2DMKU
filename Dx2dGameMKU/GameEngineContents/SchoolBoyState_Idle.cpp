#include "PrecompileHeader.h"
#include "SchoolBoyState_Idle.h"


#include "SchoolBoyFSM.h"

const std::string_view SchoolBoyState_Idle::AniName = "Idle";
const std::string_view SchoolBoyState_Idle::AniFileName = "SchoolBoy_Idle.png";
const std::pair<int, int> SchoolBoyState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Idle::AniInterTime = 0.08f;

SchoolBoyState_Idle::SchoolBoyState_Idle()
{

}

SchoolBoyState_Idle::~SchoolBoyState_Idle()
{

}

void SchoolBoyState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

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
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//���� ���·� �ٲٰų� Idle�� �����ϴ� ���
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle ���ð��� ���������� �̵����·� ����
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;


	GetFSM()->ChangeState(SchoolBoyStateType::Walk);
}



