#include "PrecompileHeader.h"
#include "GatherEnergyEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"


const std::string_view GatherEnergyEffect::Light_FileName = "ClearLight.png";
const float4 GatherEnergyEffect::LightScale = {256.f, 256.f};

const size_t GatherEnergyEffect::ParticleCount = 30;
const float4 GatherEnergyEffect::ParticleScale = {32.f, 32.f};

GatherEnergyEffect::GatherEnergyEffect()
{

}

GatherEnergyEffect::~GatherEnergyEffect()
{

}


void GatherEnergyEffect::Start()
{
	GameEngineActor::Start();

	ImageLoad();
	CreateRenders();
	Off();
}

void GatherEnergyEffect::ImageLoad()
{
	if (nullptr != GameEngineTexture::Find(Light_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	GameEngineTexture::Load(Dir.GetPlusFileName(Light_FileName).GetFullPath());
}

void GatherEnergyEffect::CreateRenders() 
{
	Light = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Light->SetTexture(Light_FileName);
	Light->Off();

	/*ReadyParticles.resize(ParticleCount);
	
	for (ParticleData& ParticleInfo : ReadyParticles)
	{
		ParticleInfo.Render = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
		ParticleInfo.Render->SetMesh("Rect");
		ParticleInfo.Render->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
		ParticleInfo.Render->GetShaderResHelper().SetConstantBufferLink("LinkColor", ParticleInfo.Color);
		ParticleInfo.Render->Off();

		GameEngineTransform* RenderTrans = ParticleInfo.Render->GetTransform();
		RenderTrans->SetLocalScale(ParticleScale);
	}*/

}

void GatherEnergyEffect::Excute(float4 _LightColor, float _Duration /*= 0.5f*/)
{
	On();
	Light->On();

	Timer = 0.f;
	Duration = _Duration;

	_LightColor.a = 0.f;
	Light->ColorOptionValue.PlusColor = _LightColor;

	//ParticleCreateTime = Duration / static_cast<float>(ParticleCount);
}


void GatherEnergyEffect::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	Timer += _DeltaTime;
	Update_Light();
	/*float NowInstanceTime = ParticleCreateTime * static_cast<float>(ActionParticles.size());
	if (NowInstanceTime < Timer)
	{
		InstanceParticle();
	}*/

	if (Timer < Duration)
		return;

	Off();
}


void GatherEnergyEffect::Update_Light()
{
	float Ratio = (Timer / Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float4 NowScale = float4::LerpClamp(float4::Zero, LightScale, Ratio);
	Light->GetTransform()->SetLocalScale(NowScale);
	Light->ColorOptionValue.MulColor.a = (1.f - Ratio);
}



void GatherEnergyEffect::InstanceParticle()
{
	if (true == ReadyParticles.empty())
		return;

	ParticleData& Particle = ReadyParticles.back();
	ReadyParticles.pop_back();

	float RandAngle = GameEngineRandom::MainRandom.RandomFloat(0.f, 360.f);
	float4 RandDir = float4::AngleToDirection2DToDeg(RandAngle);

	Particle.Color.a = 0.f;
	Particle.Dir = RandDir;
	Particle.Render->On();
	//Particle.Duration = 

	ActionParticles.push_back(Particle);
}
