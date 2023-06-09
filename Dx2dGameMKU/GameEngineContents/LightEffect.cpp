#include "PrecompileHeader.h"
#include "LightEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"


const std::string_view LightEffect::Light_FileName = "ClearLight.png";
const float4 LightEffect::LightScale = { 256.f, 256.f };


LightEffect::LightEffect()
{

}

LightEffect::~LightEffect()
{

}


void LightEffect::Start()
{
	GameEngineActor::Start();

	ImageLoad();
	CreateRenders();
	Off();
}

void LightEffect::ImageLoad()
{
	if (nullptr != GameEngineTexture::Find(Light_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	GameEngineTexture::Load(Dir.GetPlusFileName(Light_FileName).GetFullPath());
}

void LightEffect::CreateRenders()
{
	Light = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Light->SetTexture(Light_FileName);
	Light->Off();
}

void LightEffect::Flicker(float4 _LightColor, float _Duration /*= 0.5f*/)
{
	On();
	Light->On();

	Timer = 0.f;
	Duration = _Duration;

	_LightColor.a = 0.f;
	Light->ColorOptionValue.PlusColor = _LightColor;
}


void LightEffect::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	Timer += _DeltaTime;
	Update_Flickering();
}


void LightEffect::Update_Flickering()
{
	float Ratio = (Timer / Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float4 NowScale = float4::LerpClamp(float4::Zero, LightScale, Ratio);
	Light->GetTransform()->SetLocalScale(NowScale);
	Light->ColorOptionValue.MulColor.a = (1.f - Ratio);

	if (Timer < Duration)
		return;

	Off();
}
