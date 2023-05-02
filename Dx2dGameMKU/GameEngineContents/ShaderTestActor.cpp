#include "PrecompileHeader.h"
#include "ShaderTestActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"

ShaderTestActor::ShaderTestActor()
{

}

ShaderTestActor::~ShaderTestActor()
{

}

void ShaderTestActor::Start()
{
	const float4 RenderScale = float4{ 200.f, 200.f, 1.f };

	/*std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("Burn");
	Render1->GetShaderResHelper().SetConstantBufferLink("NoiseFilter", LinkData);
	Render1->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, "RCG_Kyoko_idle0001_anio.png");
	Render1->GetTransform()->SetLocalScale(RenderScale);*/

	LinkData.y = 5.f;
}


void ShaderTestActor::Update(float _DeltaTime)
{
	Timer += _DeltaTime;
	LinkData.x = abs(sinf(Timer));
}

