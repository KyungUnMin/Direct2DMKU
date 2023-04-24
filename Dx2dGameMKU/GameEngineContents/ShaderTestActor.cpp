#include "PrecompileHeader.h"
#include "ShaderTestActor.h"
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderer.h>


ShaderTestActor::ShaderTestActor()
{

}

ShaderTestActor::~ShaderTestActor()
{

}

void ShaderTestActor::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResource");
	Dir.Move("ContentsResource");
	Dir.Move("Shader");
	Dir.Move("RCGShader");
	
	GameEnginePath ShaderPath = Dir.GetPlusFileName("ContentsShaderTest.hlsl");
	GameEngineVertexShader::Load(ShaderPath.GetFullPath(), "Texture_VS");
	GameEnginePixelShader::Load(ShaderPath.GetFullPath(), "Texture_PS");

	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("MyTexture");
	Pipe->SetVertexBuffer("Rect");
	Pipe->SetVertexShader(ShaderPath.GetFileName());
	Pipe->SetPixelShader(ShaderPath.GetFileName());
	Pipe->SetIndexBuffer("Rect");
	Pipe->SetRasterizer("EngineBase");


	RenderPtr = CreateComponent<GameEngineRenderer>();
	RenderPtr->SetPipeLine("MyTexture");
	RenderPtr->GetShaderResHelper().SetConstantBufferLink("CTime", Timer);

	RenderPtr->GetTransform()->SetLocalScale({ 100.f, 200.f, 100.f });
	RenderPtr->GetShaderResHelper().SetTexture("DiffuseTex", "RCG_Kyoko_battlestart0026_anio.png");


}

void ShaderTestActor::Update(float _DeltaTime)
{
	Timer.x += _DeltaTime;
}
