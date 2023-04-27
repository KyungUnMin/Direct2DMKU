#include "PrecompileHeader.h"
#include "RCG_GameCore.h"

#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#include "RCGDefine.h"

void RCG_GameCore::ContentsResourceInit()
{
	LoadShaders();
	CreateBlends();
	CreateRenderingPipeLine();
}



void RCG_GameCore::LoadShaders() 
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Shader);
	std::vector<GameEngineFile> ShaderFiles = Dir.GetAllFile({ ".hlsl" });
	
	for (const GameEngineFile& File : ShaderFiles)
	{
		GameEngineVertexShader::Load(File.GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(File.GetFullPath(), "Texture_PS");
	}
}

void RCG_GameCore::CreateBlends()
{
	
}

void RCG_GameCore::CreateRenderingPipeLine()
{
	std::shared_ptr<GameEngineRenderingPipeLine> FieldDoor = GameEngineRenderingPipeLine::Create("FieldDoor");
	FieldDoor->SetVertexBuffer("Rect");
	FieldDoor->SetVertexShader("FieldDoor.hlsl");
	FieldDoor->SetIndexBuffer("Rect");
	FieldDoor->SetRasterizer("Engine2DBase");
	FieldDoor->SetPixelShader("FieldDoor.hlsl");
	FieldDoor->SetBlendState("AlphaBlend");
	FieldDoor->SetDepthState("EngineDepth");
}