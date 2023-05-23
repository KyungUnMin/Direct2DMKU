#include "PrecompileHeader.h"
#include "DapEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "FieldPlayer.h"


const std::string_view DapEffect::RenderPipeName = "DirectColor";
const std::string_view DapEffect::EffectImgName = "Player_DapEffect.png";
float4 DapEffect::EffectScale = float4::Zero;

const float DapEffect::MoveOffset = 100.f;
float4 DapEffect::StartOffset = float4::Zero;
float4 DapEffect::DestOffset = float4::Zero;


DapEffect::DapEffect()
{

}

DapEffect::~DapEffect()
{

}

void DapEffect::Start()
{
	GameEngineActor::Start();

	LoadEffectImage();
	CreateRender();
	Off();
}

void DapEffect::LoadEffectImage()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("SpecialAttack");
	EffectScale = GameEngineTexture::Load(Dir.GetPlusFileName(EffectImgName).GetFullPath())->GetScale();

	EffectScale *= 2.7f;//RCGDefine::ResourceScaleConvertor;
	StartOffset = float4::Up * EffectScale.hy();
	DestOffset = StartOffset + (float4::Left * MoveOffset);
}

void DapEffect::CreateRender() 
{
	RenderPtr = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	RenderPtr->SetPipeLine(RenderPipeName);
	RenderPtr->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, EffectImgName);
	RenderPtr->GetShaderResHelper().SetConstantBufferLink("LinkColor", ShaderLinkColor);

	GameEngineTransform* RenderTrans = RenderPtr->GetTransform();
	RenderTrans->SetLocalScale(EffectScale);
	RenderTrans->SetLocalPosition(float4::Forward);
}






void DapEffect::Init()
{
	On();
	Timer = 0.f;
	SettingColor();
}

void DapEffect::SettingColor()
{
	//1¾È
	{
		ShaderLinkColor.r = GetStepRand();
		ShaderLinkColor.g = GetStepRand();
		ShaderLinkColor.b = GetStepRand();
	}


	//2¾È
	/*{
		static UINT Count = 0;
		UINT  ModValue = (Count++) % 3;
		if (0 == ModValue)
		{
			ShaderLinkColor.r = 0.0f;
			ShaderLinkColor.g = 1.0f;
			ShaderLinkColor.b = 1.0f;
		}
		else if (1 == ModValue)
		{
			ShaderLinkColor.r = 1.0f;
			ShaderLinkColor.g = 0.0f;
			ShaderLinkColor.b = 1.0f;
		}
		else
		{
			ShaderLinkColor.r = 1.0f;
			ShaderLinkColor.g = 1.0f;
			ShaderLinkColor.b = 1.0f;
		}
	}*/

	ShaderLinkColor.a = 1.f;
}


float DapEffect::GetStepRand(float _StepValue /*= 0.3f*/)
{
	float RandValue = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);

	if (RandValue < _StepValue)
		return 1.f;

	return RandValue;
}



void DapEffect::Update(float _DeltaTime) 
{
	GameEngineActor::Update(_DeltaTime);

	Timer += _DeltaTime;
	float Ratio = (Timer / Duration);

	if (1.f < Ratio)
	{
		Off();
		return;
	}

	float4 NowOffset = float4::LerpClamp(StartOffset, DestOffset, Ratio);
	RenderPtr->GetTransform()->SetLocalPosition(NowOffset);
	//ShaderLinkColor.a = (1.f - Ratio);
	ShaderLinkColor.a = (1.f - Ratio) * 0.8f;
}

