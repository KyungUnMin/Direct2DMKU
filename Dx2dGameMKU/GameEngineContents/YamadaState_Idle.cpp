#include "PrecompileHeader.h"
#include "YamadaState_Idle.h"

#include "YamadaFSM.h"

#include "FieldEnemyBase.h"

const std::vector<int> YamadaState_Idle::FarAttackPercent = { 100, 20, 50 };
const float YamadaState_Idle::SightRadius = 100.f;

const std::string_view YamadaState_Idle::AniName = "Idle";
const std::string_view YamadaState_Idle::AniFileName = "Yamada_Idle.png";
const std::pair<int, int> YamadaState_Idle::AniCutFrame = std::pair<int, int>(5, 2);
const float YamadaState_Idle::AniInterTime = 0.08f;


YamadaState_Idle::YamadaState_Idle()
{

}

YamadaState_Idle::~YamadaState_Idle()
{

}

void YamadaState_Idle::Start() 
{
	BossState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
	EnemyStateBase::SetSight(SightRadius);
}

void YamadaState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Idle::CreateAnimation() 
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


void YamadaState_Idle::EnterState()
{
	BossState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void YamadaState_Idle::Update(float _DeltaTime) 
{
	BossState_IdleBase::Update(_DeltaTime);

	
	//���� ���·� �ٲٰų� Idle�� �����ϴ� ���
	/*if (true == EnemyState_IdleBase::ChangeAttackState())
		return;*/

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	////0�� Phase�϶�  ���Ÿ� ���� ����
	//size_t CurPhase = GetBossFsm()->GetCurPhase();
	//if(0 != CurPhase)
	//{
	//	//���ڷ� �� Ȯ���� ���� ���Ÿ� ���� �õ�
	//	if (true == EnemyStateBase::FarAttackExcute(FarAttackPercent[CurPhase]))
	//		return;
	//}


	//Idle ���ð��� ���������� �̵����·� ����
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;


	GetFSM()->ChangeState(YamadaStateType::Walk);
}

