#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Render(float _DeltaTime)
{
	if (nullptr == Pipe)
	{
		MsgAssert("아직 렌더러에 렌더링 파이프라인을 설정해주지 않았습니다");
		return;
	}

	Pipe->Render();
}


void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == Pipe)
	{
		MsgAssert("존재하지 않는 이름의 렌더링 파이프 라인입니다");
		return;
	}

	//버텍스 쉐이더의 상수버퍼, 텍스처 등의 세터들을 ShaderResHelper에 저장한다
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	//픽셀 쉐이더의 상수버퍼, 텍스처 등의 세터들을 ShaderResHelper에 저장한다
	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

}

