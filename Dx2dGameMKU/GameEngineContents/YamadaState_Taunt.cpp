#include "PrecompileHeader.h"
#include "YamadaState_Taunt.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "SoundMgr.h"
#include "YamadaFSM.h"

#include "FieldEnemyBase.h"

const std::string_view YamadaState_Taunt::AniName = "Taunt";
const std::string_view YamadaState_Taunt::AniFileName = "Yamada_Taunt.png";
const std::pair<int, int> YamadaState_Taunt::AniCutFrame = std::pair<int, int>(5, 2);
const float YamadaState_Taunt::AniInterTime = 0.08f;

YamadaState_Taunt::YamadaState_Taunt()
{

}

YamadaState_Taunt::~YamadaState_Taunt()
{

}

void YamadaState_Taunt::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Taunt::LoadAnimation()
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

void YamadaState_Taunt::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}


void YamadaState_Taunt::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayLaughSFX();
}

void YamadaState_Taunt::PlayLaughSFX()
{
	std::string SfxName = "Yamada_Laugh";

	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 5);
	SfxName += GameEngineString::ToString(RandNum);
	SfxName += ".wav";

	SoundMgr::PlaySFX(SfxName);
}


void YamadaState_Taunt::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 100);
	if (RandNum < 25)
	{
		GetFSM()->ChangeState(YamadaStateType::MatterCrush);
	}
	else if(RandNum < 50)
	{
		GetFSM()->ChangeState(YamadaStateType::ForceField);
	}
	else if (RandNum < 75)
	{
		GetFSM()->ChangeState(YamadaStateType::Wormchi);
	}
	else
	{
		GetFSM()->ChangeState(YamadaStateType::TeleportDisappear);
	}
}



