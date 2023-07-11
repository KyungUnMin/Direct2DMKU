#include "PrecompileHeader.h"
#include "YamadaState_PhaseTransition.h"


#include "YamadaFSM.h"
#include "SoundMgr.h"

#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "TownBossLevel.h"

const std::string_view YamadaState_PhaseTransition::AniName = "PhaseTransition";
const std::string_view YamadaState_PhaseTransition::AniFileName = "Yamada_PhaseTransition.png";
const std::pair<int, int> YamadaState_PhaseTransition::AniCutFrame = std::pair<int, int>(5, 3);
const float YamadaState_PhaseTransition::AniInterTime = 0.08f;

YamadaState_PhaseTransition::YamadaState_PhaseTransition()
{

}

YamadaState_PhaseTransition::~YamadaState_PhaseTransition()
{

}

void YamadaState_PhaseTransition::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
	BindNightBackImage();
}

void YamadaState_PhaseTransition::LoadAnimation()
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

void YamadaState_PhaseTransition::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 12,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}

void YamadaState_PhaseTransition::BindNightBackImage()
{
	std::shared_ptr<TownBossLevel> Level = nullptr;
	Level = std::dynamic_pointer_cast<TownBossLevel>(FieldLevelBase::GetPtr());
	if (nullptr == Level)
	{
		MsgAssert("보스 Yamada가 TownLevel에서 생성되지 않았습니다");
		return;
	}

	Night = Level->GetNightBackImg();
}


void YamadaState_PhaseTransition::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	Night->On();
	Night->ColorOptionValue.MulColor.a = 0.f;

	SoundMgr::PlaySFX("Yamada_PhaseTransition_Voice.wav").SetVolume(3.f);
	SoundMgr::PlaySFX("Yamada_PhaseTransition_Effect.wav").SetVolume(2.f);
}


void YamadaState_PhaseTransition::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	static const float NightDuration = AniInterTime * 10.f;

	float Ratio = GetLiveTime() / NightDuration;
	Ratio = std::clamp(Ratio, 0.f, 1.f);
	Night->ColorOptionValue.MulColor.a = Ratio;


	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::TeleportDisappear);
}
