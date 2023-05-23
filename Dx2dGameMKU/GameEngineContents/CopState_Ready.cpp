#include "PrecompileHeader.h"
#include "CopState_Ready.h"

#include "CopFSM.h"
#include "FieldEnemyBase.h"

const std::string_view CopState_Ready::WaitAniName = "Ready_Wait";
const std::string_view CopState_Ready::GetUpAniName = "Ready_GetUp";
const std::string_view CopState_Ready::AniFileName = "Cop_Ready.png";
const std::pair<int, int> CopState_Ready::AniCutFrame = std::pair<int, int>(5, 2);
const float CopState_Ready::AniInterTime = 0.08f;

CopState_Ready::CopState_Ready()
{

}

CopState_Ready::~CopState_Ready()
{

}

void CopState_Ready::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyStateBase::SetSight(50.f);
}

void CopState_Ready::LoadAnimation()
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

void CopState_Ready::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = WaitAniName,
		.SpriteName = AniFileName,
		.Start = 1,
		.End = 1,
		.FrameInter = FLT_MAX,
	});

	GetRenderer()->CreateAnimation
	({
		.AnimationName = GetUpAniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.FrameIndex = std::vector<size_t>{2, 3, 4, 5, 0}
	});


}


void CopState_Ready::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(WaitAniName);

	//Ready�� �÷��̾� ��ġ�� ������� ������ ������ �����ϱ� ������,
	//EnemyStateBase::EnterState()���� ������ ������ �ٽ� ������ ���������� ����
	GetEnemy()->GetTransform()->SetLocalPositiveScaleX();
}


void CopState_Ready::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case CopState_Ready::State::Wait:
		Update_Wait();
		break;
	case CopState_Ready::State::GetUp:
		Update_GetUp();
		break;
	}
}

void CopState_Ready::Update_Wait()
{
	float4 DirToPlayer = EnemyStateBase::GetVecToPlayer();
	float Distance = DirToPlayer.Size();

	if (GetSightRadius() < Distance)
		return;

	GetRenderer()->ChangeAnimation(GetUpAniName);
	CurState = State::GetUp;
}

void CopState_Ready::Update_GetUp() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CopStateType::Idle);
}

