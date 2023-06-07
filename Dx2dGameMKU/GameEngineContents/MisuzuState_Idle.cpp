#include "PrecompileHeader.h"
#include "MisuzuState_Idle.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "MisuzuFSM.h"

#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Idle::AniName = "Idle";
const std::string_view MisuzuState_Idle::AniFileName = "Misuzu_Idle.png";
const std::pair<int, int> MisuzuState_Idle::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Idle::AniInterTime = 0.08f;

MisuzuState_Idle::MisuzuState_Idle()
{

}

MisuzuState_Idle::~MisuzuState_Idle()
{

}

void MisuzuState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Idle::CreateAnimation() 
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


void MisuzuState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void MisuzuState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//인자로 들어간 확률에 맞춰 원거리 공격 시도
	if (true == FarAttackExcute(100))
		return;

	//공격 상태로 바꾸거나 Idle을 유지하는 경우
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle 대기시간이 끝났을때만 이동상태로 변경
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;


	GetFSM()->ChangeState(MisuzuStateType::Walk);
}


bool MisuzuState_Idle::FarAttackExcute(int _Percent)
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 100);

	//확률을 뚫지 못한 경우
	if (_Percent < RandValue)
		return false;

	size_t FarAttack = GetEnemyFsm()->GetRandomFarAttack();

	//해당 Phase에서는 원거리 공격이 없는 경우
	if (-1 == FarAttack)
		return false;

	GetFSM()->ChangeState(FarAttack);
	return true;
}