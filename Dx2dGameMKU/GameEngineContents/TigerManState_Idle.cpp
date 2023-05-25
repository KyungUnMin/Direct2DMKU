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
		.Start = 0,
		.End = 7,
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


	//���� ���·� �ٲٰų� Idle�� �����ϴ� ���
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle ���ð��� ���������� �̵����·� ����
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;

	GetFSM()->ChangeState(TigerManStateType::Walk);
	
}



