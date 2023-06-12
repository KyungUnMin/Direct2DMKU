#include "PrecompileHeader.h"
#include "CheerleaderState_Idle.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "CheerleaderFSM.h"

const std::string_view CheerleaderState_Idle::AniName = "Idle";
const std::string_view CheerleaderState_Idle::AniFileName = "Cheerleader_Idle.png";
const std::pair<int, int> CheerleaderState_Idle::AniCutFrame = std::pair<int, int>(5, 3);
const float CheerleaderState_Idle::AniInterTime = 0.08f;
const int CheerleaderState_Idle::CartWheelPercent = 10;

CheerleaderState_Idle::CheerleaderState_Idle()
{

}

CheerleaderState_Idle::~CheerleaderState_Idle()
{

}

void CheerleaderState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

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
		.End = 11,
		.FrameInter = AniInterTime
	});
}


void CheerleaderState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void CheerleaderState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//CartWheelPercent�� Ȯ���� FSM�� CartWheel�� ��ü
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (RandValue < CartWheelPercent)
	{
		GetFSM()->ChangeState(CheerleaderStateType::CartWheel);
		return;
	}
	


	//���� ���·� �ٲٰų� Idle�� �����ϴ� ���
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle ���ð��� ���������� �̵����·� ����
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;


	GetFSM()->ChangeState(CheerleaderStateType::Walk);

}



