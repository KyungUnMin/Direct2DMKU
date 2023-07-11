#include "PrecompileHeader.h"
#include "YamadaState_TeleportDisappear.h"

#include <GameEngineBase/GameEngineRandom.h>


#include "YamadaFSM.h"

#include "FieldEnemyBase.h"

const std::string_view YamadaState_TeleportDisappear::AniName = "TeleportDisappear";
const std::string_view YamadaState_TeleportDisappear::AniFileName = "Yamada_TeleportDisappear.png";
const std::pair<int, int> YamadaState_TeleportDisappear::AniCutFrame = std::pair<int, int>(5, 2);
const float YamadaState_TeleportDisappear::AniInterTime = 0.08f;

const std::vector<std::string_view> YamadaState_TeleportDisappear::LaughSfx =
{
	"Yamada_Laugh0.wav",
	"Yamada_Laugh2.wav",
	"Yamada_Laugh3.wav",
};

YamadaState_TeleportDisappear::YamadaState_TeleportDisappear()
{

}

YamadaState_TeleportDisappear::~YamadaState_TeleportDisappear()
{

}

void YamadaState_TeleportDisappear::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
	ShadowRender = GetEnemy()->GetShadowRender();
}

void YamadaState_TeleportDisappear::LoadAnimation()
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

void YamadaState_TeleportDisappear::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(AniName, 3, [this]()
	{
		EnemyStateBase::OffMainCollider();

		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(LaughSfx.size() - 1));
		const std::string_view& SfxName = LaughSfx[static_cast<size_t>(RandNum)];
		SoundMgr::PlaySFX(SfxName).SetVolume(3.f);
	});
}


void YamadaState_TeleportDisappear::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EffectSfx = SoundMgr::PlaySFX("Yamada_TeleportDistappear_Effect.wav");
	EffectSfx.SetPitch(1.5f);
}




void YamadaState_TeleportDisappear::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	Update_ShadowScale();

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(YamadaStateType::TeleportAppear);
}

void YamadaState_TeleportDisappear::Update_ShadowScale()
{
	float Ratio = (GetLiveTime() / ShadowDuration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);
	ShadowRender->ColorOptionValue.MulColor = float4::One * (1.f - Ratio);
}


void YamadaState_TeleportDisappear::ExitState()
{
	EnemyStateBase::ExitState();
	EnemyStateBase::OnMainCollider();
	ShadowRender->ColorOptionValue.MulColor = float4::One;
	
	EffectSfx.Stop();
}