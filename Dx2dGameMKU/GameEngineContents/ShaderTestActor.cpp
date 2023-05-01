#include "PrecompileHeader.h"
#include "ShaderTestActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>


ShaderTestActor::ShaderTestActor()
{

}

ShaderTestActor::~ShaderTestActor()
{

}

void ShaderTestActor::Start()
{
	const float4 RenderScale = float4{ 550.f, 180.f, 1.f };

	std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("ShaderTest");
	Render1->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);
	Render1->GetTransform()->SetLocalScale(RenderScale);
	Render1->GetTransform()->AddLocalPosition(float4::Left * RenderScale.hx());

	std::shared_ptr<GameEngineRenderer> Render2 = CreateComponent<GameEngineRenderer>();
	Render2->SetPipeLine("ShaderTest");
	Render2->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);
	Render2->GetTransform()->SetLocalScale(RenderScale * float4{ -1.f, 1.f, 1.f });
	Render2->GetTransform()->AddLocalPosition(float4::Right * RenderScale.hx());
}


void ShaderTestActor::Update(float _DeltaTime)
{
	Data.Timer += _DeltaTime;
}

