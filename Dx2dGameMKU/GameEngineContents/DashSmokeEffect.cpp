#include "PrecompileHeader.h"
#include "DashSmokeEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

const std::string_view DashSmokeEffect::FileName = "DashSmoke.png";
const float DashSmokeEffect::AniInter = 0.1f;
const float4 DashSmokeEffect::RenderScale = float4{ 64.f, 64.f };

DashSmokeEffect::DashSmokeEffect()
{

}

DashSmokeEffect::~DashSmokeEffect()
{

}

void DashSmokeEffect::Start()
{
	GameEngineActor::Start();

	ImageLoad();
	CreateAnimation();
}

void DashSmokeEffect::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(FileName).GetFullPath(), 2, 2);
	IsLoad = true;
}

void DashSmokeEffect::CreateAnimation()
{
	Render = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->CreateAnimation
	({
		.AnimationName = FileName,
		.SpriteName = FileName,
		.FrameInter = AniInter,
		.Loop = false,
	});

	Render->ChangeAnimation(FileName);
	Render->GetTransform()->SetLocalScale(RenderScale);
}

void DashSmokeEffect::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	float LiveTime = GetLiveTime();
	float Duration = AniInter * 4.f;
	float Ratio = (LiveTime / Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	Render->ColorOptionValue.MulColor.a = (1.f - Ratio);

	if (false == Render->IsAnimationEnd())
		return;

	Death();
}
