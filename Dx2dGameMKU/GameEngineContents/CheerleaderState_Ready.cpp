#include "PrecompileHeader.h"
#include "CheerleaderState_Ready.h"

#include "CheerleaderFSM.h"
#include "FieldEnemyBase.h"

const std::string_view CheerleaderState_Ready::WaitAniName = "Ready_Wait";
const std::string_view CheerleaderState_Ready::GetUpAniName = "Ready_GetUp";
const std::string_view CheerleaderState_Ready::AniFileName = "Cheerleader_Ready.png";
const std::pair<int, int> CheerleaderState_Ready::AniCutFrame = std::pair<int, int>(5, 2);
const float CheerleaderState_Ready::AniInterTime = 0.08f;

CheerleaderState_Ready::CheerleaderState_Ready()
{

}

CheerleaderState_Ready::~CheerleaderState_Ready()
{

}

void CheerleaderState_Ready::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	EnemyStateBase::SetSight(50.f);
}

void CheerleaderState_Ready::LoadAnimation()
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

void CheerleaderState_Ready::CreateAnimation()
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


void CheerleaderState_Ready::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(WaitAniName);

	//Ready는 플레이어 위치와 상관없이 렌더러 방향을 설정하기 때문에,
	//EnemyStateBase::EnterState()에서 설정된 방향을 다시 무조껀 오른쪽으로 변경
	GetEnemy()->GetTransform()->SetLocalPositiveScaleX();
}


void CheerleaderState_Ready::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case CheerleaderState_Ready::State::Wait:
		Update_Wait();
		break;
	case CheerleaderState_Ready::State::GetUp:
		Update_GetUp();
		break;
	}
}

void CheerleaderState_Ready::Update_Wait()
{
	float4 DirToPlayer = EnemyStateBase::GetVecToPlayer();
	float Distance = DirToPlayer.Size();

	if (GetSightRadius() < Distance)
		return;

	GetRenderer()->ChangeAnimation(GetUpAniName);
	CurState = State::GetUp;
}

void CheerleaderState_Ready::Update_GetUp() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(CheerleaderStateType::Idle);
}

