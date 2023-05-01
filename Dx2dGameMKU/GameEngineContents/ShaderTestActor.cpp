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
	/*const float4 RenderScale = float4{ 550.f, 180.f, 1.f };

	std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("ShaderTest");
	Render1->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);
	Render1->GetTransform()->SetLocalScale(RenderScale);
	Render1->GetTransform()->AddLocalPosition(float4::Left * RenderScale.hx());*/
}


void ShaderTestActor::Update(float _DeltaTime)
{
	
}

