#include "PrecompileHeader.h"
#include "NoiseState_Walk.h"

#include "NoiseFSM.h"

#include "BossFSMBase.h"
#include "NoiseState_Idle.h"

const std::string_view NoiseState_Walk::AniName = "Walk";
const std::string_view NoiseState_Walk::AniFileName = "Noise_Walk.png";
const std::pair<int, int> NoiseState_Walk::AniCutFrame = std::pair<int, int>(5, 2);
const float NoiseState_Walk::AniInterTime = 0.08f;

NoiseState_Walk::NoiseState_Walk()
{

}

NoiseState_Walk::~NoiseState_Walk()
{

}


void NoiseState_Walk::Start()
{
	EnemyState_WalkBase::Start();

	LoadAnimation();
	CreateAnimation();
	BossFsmPtr = GetConvertFSM<BossFSMBase>();
	EnemyStateBase::SetSight(NoiseState_Idle::SightRadius * 0.8f);

	EnemyState_WalkBase::SetNextState(NoiseStateType::Idle);
}

void NoiseState_Walk::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void NoiseState_Walk::CreateAnimation()
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


void NoiseState_Walk::EnterState()
{
	EnemyState_WalkBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}

bool NoiseState_Walk::ChangeStateWhenFarWithAwayPlayer()
{
	//0�� Phase�϶�  ���Ÿ� ���� ����
	size_t CurPhase = BossFsmPtr->GetCurPhase();
	if (0 == CurPhase)
		return false;

	//���ڷ� �� Ȯ���� ���� ���Ÿ� ���� �õ�
	return EnemyStateBase::FarAttackExcute(NoiseState_Idle::FarAttackPercent[CurPhase]);
}

