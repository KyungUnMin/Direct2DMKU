#include "PrecompileHeader.h"
#include "RCG_GameCore.h"

#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineGUI.h>

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
		//GameEngineShader::AutoCompile()
		GameEngineVertexShader::Load(File.GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(File.GetFullPath(), "Texture_PS");
	}
}

void RCG_GameCore::CreateBlends()
{
	
}

void RCG_GameCore::CreateRenderingPipeLine()
{
	ClonePipeLineForShader("FieldDoor", "FieldDoor.hlsl");
	ClonePipeLineForShader("DirectColor", "DirectColor.hlsl");
	ClonePipeLineForShader("Tile", "Tile.hlsl");
	ClonePipeLineForShader("MpBar", "MpBar.hlsl");

	ClonePipeLineForShader("GlichStair", "GlichStair.hlsl");
	//ClonePipeLineForShader("ColorWave", "ColorWave.hlsl");

	ClonePipeLineForShader("Burn", "Burn.hlsl");
}

void RCG_GameCore::ClonePipeLineForShader(const std::string_view& _PipeName, const std::string_view& _ShaderName)
{
	std::shared_ptr<GameEngineRenderingPipeLine> PipeLine = GameEngineRenderingPipeLine::Create(_PipeName);
	PipeLine->SetVertexBuffer("Rect");
	PipeLine->SetVertexShader(_ShaderName);
	PipeLine->SetIndexBuffer("Rect");
	PipeLine->SetRasterizer("Engine2DBase");
	PipeLine->SetPixelShader(_ShaderName);
	PipeLine->SetBlendState("AlphaBlend");
	PipeLine->SetDepthState("EngineDepth");
}