#include "PrecompileHeader.h"
#include "CopState_Idle.h"


#include "CopFSM.h"

const std::string_view CopState_Idle::AniName = "Idle";
const std::string_view CopState_Idle::AniFileName = "Cop_Idle.png";
const std::pair<int, int> CopState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float CopState_Idle::AniInterTime = 0.08f;

CopState_Idle::CopState_Idle()
{

}

CopState_Idle::~CopState_Idle()
{

}

void CopState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CopState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cop");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CopState_Idle::CreateAnimation() 
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


void CopState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void CopState_Idle::Update(float _DeltaTime) 
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

	GetFSM()->ChangeState(CopStateType::Walk);
	
}



