#include "PrecompileHeader.h"
#include "HitEffect.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

const std::string_view HitEffect::HitAir_FileName = "HitAir.png";
const std::string_view HitEffect::HitSpark_FileName = "HitSpark.png";
float4 HitEffect::SparkScale = float4::Zero;


HitEffect::HitEffect()
{

}

HitEffect::~HitEffect()
{

}


void HitEffect::Start()
{
	GameEngineActor::Start();

	LoadImages();
	CreateRenders();
}

void HitEffect::LoadImages()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	GameEngineTexture::Load(Dir.GetPlusFileName(HitAir_FileName).GetFullPath());

	const size_t XCount = 4;
	const size_t YCount = 2;
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::LoadSheet(Dir.GetPlusFileName(HitSpark_FileName).GetFullPath(), XCount, YCount);
	float4 SparkTexScale = Sprite->GetSpriteInfo(0).Texture->GetScale();
	SparkTexScale.x /= static_cast<float>(XCount);
	SparkTexScale.y /= static_cast<float>(YCount);
	SparkTexScale.z = 1.f;
	SparkScale = SparkTexScale;

	IsLoad = true;
}

void HitEffect::CreateRenders() 
{
	AirRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	AirRender->SetTexture(HitAir_FileName);

	static const std::string_view AniName = "Spark";
	SparkRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	SparkRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = HitSpark_FileName,
		.Start = 0,
		.End = 6,
		.FrameInter = 0.02f,
		.Loop = false,
	});

	SparkRender->ChangeAnimation(AniName);
	SparkRender->GetTransform()->SetLocalScale(SparkScale);
}

void HitEffect::Update(float _DeltaTime) 
{
	GameEngineActor::Update(_DeltaTime);

	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / Duration);

	const float AlphaColor = std::clamp(1.f - Ratio, 0.f, 1.f);
	const float4 MulColor = float4{ 1.f, 1.f, 1.f, AlphaColor };

	float4 NowAirScale = float4::LerpClamp(float4::Zero, AirMaxScale, Ratio);
	AirRender->GetTransform()->SetLocalScale(NowAirScale);

	AirRender->ColorOptionValue.MulColor = MulColor;
	//SparkRender->ColorOptionValue.MulColor = MulColor;

	if (true == SparkRender->IsAnimationEnd())
	{
		SparkRender->Off();
	}

	if (Ratio < 1.f)
		return;

	Death();
}


void HitEffect::OffHitSpark()
{
	SparkRender->Off();
}

void HitEffect::OffHitAir()
{
	AirRender->Off();
}