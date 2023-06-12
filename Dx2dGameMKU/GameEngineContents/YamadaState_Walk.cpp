#include "PrecompileHeader.h"
#include "YamadaState_Walk.h"

#include "YamadaFSM.h"

#include "BossFSMBase.h"
#include "YamadaState_Idle.h"

const std::string_view YamadaState_Walk::AniName = "Walk";
const std::string_view YamadaState_Walk::AniFileName = "Yamada_Walk.png";
const std::pair<int, int> YamadaState_Walk::AniCutFrame = std::pair<int, int>(5, 3);
const float YamadaState_Walk::AniInterTime = 0.08f;

YamadaState_Walk::YamadaState_Walk()
{

}

YamadaState_Walk::~YamadaState_Walk()
{

}


void YamadaState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();
	BossFsmPtr = GetConvertFSM<BossFSMBase>();
	EnemyStateBase::SetSight(YamadaState_Idle::SightRadius * 0.8f);

	EnemyState_WalkBase::SetNextState(YamadaStateType::Idle);
}

void YamadaState_Walk::LoadAnimation()
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

void YamadaState_Walk::CreateAnimation()
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


void YamadaState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}

bool YamadaState_Walk::ChangeStateWhenFarWithAwayPlayer()
{
	return false;

	//0번 Phase일땐  원거리 공격 없음
	size_t CurPhase = BossFsmPtr->GetCurPhase();
	if (0 == CurPhase)
		return false;

	//인자로 들어간 확률에 맞춰 원거리 공격 시도
	return EnemyStateBase::FarAttackExcute(YamadaState_Idle::FarAttackPercent[CurPhase]);
}

