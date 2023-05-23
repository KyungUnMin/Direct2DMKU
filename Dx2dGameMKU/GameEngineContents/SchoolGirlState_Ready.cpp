#include "PrecompileHeader.h"
#include "SchoolGirlState_Ready.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"

const std::string_view SchoolGirlState_Ready::WaitAniName = "Ready_Wait";
const std::string_view SchoolGirlState_Ready::GetUpAniName = "Ready_GetUp";
const std::string_view SchoolGirlState_Ready::AniFileName = "SchoolGirl_Ready.png";
const std::pair<int, int> SchoolGirlState_Ready::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolGirlState_Ready::AniInterTime = 0.08f;

SchoolGirlState_Ready::SchoolGirlState_Ready()
{

}

SchoolGirlState_Ready::~SchoolGirlState_Ready()
{

}

void SchoolGirlState_Ready::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyStateBase::SetSight(50.f);
}

void SchoolGirlState_Ready::LoadAnimation()
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

void SchoolGirlState_Ready::CreateAnimation()
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
		.Start = 1,
		.End = 5,
		.FrameInter = AniInterTime,
	});


}


void SchoolGirlState_Ready::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(WaitAniName);

	//Ready는 플레이어 위치와 상관없이 렌더러 방향을 설정하기 때문에,
	//EnemyStateBase::EnterState()에서 설정된 방향을 다시 무조껀 오른쪽으로 변경
	GetEnemy()->GetTransform()->SetLocalPositiveScaleX();
}


void SchoolGirlState_Ready::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case SchoolGirlState_Ready::State::Wait:
		Update_Wait();
		break;
	case SchoolGirlState_Ready::State::GetUp:
		Update_GetUp();
		break;
	}
}

void SchoolGirlState_Ready::Update_Wait()
{
	float4 DirToPlayer = EnemyStateBase::GetVecToPlayer();
	float Distance = DirToPlayer.Size();

	if (GetSightRadius() < Distance)
		return;

	GetRenderer()->ChangeAnimation(GetUpAniName);
	CurState = State::GetUp;
}

void SchoolGirlState_Ready::Update_GetUp() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Idle);
}

