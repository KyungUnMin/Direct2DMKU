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
	const float4 RenderScale = float4{ 600.f, 600.f, 1.f };

	//std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>();
	//Render1->SetPipeLine("Bloom2D");
	//Render1->GetShaderResHelper().SetConstantBufferLink("BloomData", LinkData);
	//Render1->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, "fx_diamond01.png");
	//Render1->GetTransform()->SetLocalScale(RenderScale);


}


void ShaderTestActor::Update(float _DeltaTime)
{
	static float Timer = 0.f;
	Timer += _DeltaTime;
	LinkData.LinkData2.x = abs(sinf(Timer)) * 2.f;
}

