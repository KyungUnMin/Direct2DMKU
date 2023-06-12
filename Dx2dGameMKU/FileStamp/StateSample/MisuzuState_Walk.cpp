#include "PrecompileHeader.h"
#include "MisuzuState_Walk.h"

#include "MisuzuFSM.h"

#include "BossFSMBase.h"
#include "MisuzuState_Idle.h"

const std::string_view MisuzuState_Walk::AniName = "Walk";
const std::string_view MisuzuState_Walk::AniFileName = "Misuzu_Walk.png";
const std::pair<int, int> MisuzuState_Walk::AniCutFrame = std::pair<int, int>(5, 2);
const float MisuzuState_Walk::AniInterTime = 0.08f;

MisuzuState_Walk::MisuzuState_Walk()
{

}

MisuzuState_Walk::~MisuzuState_Walk()
{

}


void MisuzuState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();
	BossFsmPtr = GetConvertFSM<BossFSMBase>();
	EnemyStateBase::SetSight(MisuzuState_Idle::SightRadius * 0.8f);

	EnemyState_WalkBase::SetNextState(MisuzuStateType::Idle);
}

void MisuzuState_Walk::LoadAnimation()
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

void MisuzuState_Walk::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 9,
		.FrameInter = AniInterTime
	});
}


void MisuzuState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}

bool MisuzuState_Walk::ChangeStateWhenFarWithAwayPlayer()
{
	//0번 Phase일땐  원거리 공격 없음
	size_t CurPhase = BossFsmPtr->GetCurPhase();
	if (0 == CurPhase)
		return false;

	//인자로 들어간 확률에 맞춰 원거리 공격 시도
	return EnemyStateBase::FarAttackExcute(MisuzuState_Idle::FarAttackPercent[CurPhase]);
}

