#include "PrecompileHeader.h"
#include "NoiseState_Taunt.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "SoundMgr.h"

#include "NoiseFSM.h"

#include "FieldEnemyBase.h"

const std::string_view NoiseState_Taunt::AniName = "Taunt";
const std::string_view NoiseState_Taunt::AniFileName = "Noise_Taunt.png";
const std::pair<int, int> NoiseState_Taunt::AniCutFrame = std::pair<int, int>(5, 4);
const float NoiseState_Taunt::AniInterTime = 0.08f;

const std::vector<std::string_view> NoiseState_Taunt::LaughSfx =
{
	"Noise_Taunt (1).wav",
	"Noise_Taunt (2).wav",
	"Noise_Taunt (3).wav",
	"Noise_Taunt (4).wav",
};

NoiseState_Taunt::NoiseState_Taunt()
{

}

NoiseState_Taunt::~NoiseState_Taunt()
{

}

void NoiseState_Taunt::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void NoiseState_Taunt::LoadAnimation()
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

void NoiseState_Taunt::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 19,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(AniName, 5, []()
	{
		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(LaughSfx.size() - 1));
		SoundMgr::PlaySFX(LaughSfx[static_cast<size_t>(RandNum)]);
	});
}



void NoiseState_Taunt::EnterState()
{
	EnemyStateBase::EnterState();
	GetRenderer()->ChangeAnimation(AniName);
}


void NoiseState_Taunt::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}



