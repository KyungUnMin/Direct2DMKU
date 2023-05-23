#include "PrecompileHeader.h"
#include "HooliganState_Ready.h"

#include "HooliganFSM.h"
#include "FieldEnemyBase.h"

const std::string_view HooliganState_Ready::WaitAniName = "Ready_Wait";
const std::string_view HooliganState_Ready::GetUpAniName = "Ready_GetUp";
const std::string_view HooliganState_Ready::AniFileName = "Hooligan_Ready.png";
const std::pair<int, int> HooliganState_Ready::AniCutFrame = std::pair<int, int>(5, 2);
const float HooliganState_Ready::AniInterTime = 0.08f;

HooliganState_Ready::HooliganState_Ready()
{

}

HooliganState_Ready::~HooliganState_Ready()
{

}

void HooliganState_Ready::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyStateBase::SetSight(50.f);
}

void HooliganState_Ready::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Hooligan");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void HooliganState_Ready::CreateAnimation()
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


void HooliganState_Ready::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(WaitAniName);

	//Ready는 플레이어 위치와 상관없이 렌더러 방향을 설정하기 때문에,
	//EnemyStateBase::EnterState()에서 설정된 방향을 다시 무조껀 오른쪽으로 변경
	GetEnemy()->GetTransform()->SetLocalPositiveScaleX();
}


void HooliganState_Ready::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case HooliganState_Ready::State::Wait:
		Update_Wait();
		break;
	case HooliganState_Ready::State::GetUp:
		Update_GetUp();
		break;
	}
}

void HooliganState_Ready::Update_Wait()
{
	float4 DirToPlayer = EnemyStateBase::GetVecToPlayer();
	float Distance = DirToPlayer.Size();

	if (GetSightRadius() < Distance)
		return;

	GetRenderer()->ChangeAnimation(GetUpAniName);
	CurState = State::GetUp;
}

void HooliganState_Ready::Update_GetUp() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(HooliganStateType::Idle);
}

