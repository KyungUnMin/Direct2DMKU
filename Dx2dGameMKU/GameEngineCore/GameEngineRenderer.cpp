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
		MsgAssert("���� �������� ������ ������������ ���������� �ʾҽ��ϴ�");
		return;
	}

	Pipe->Render();
}


void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == Pipe)
	{
		MsgAssert("�������� �ʴ� �̸��� ������ ������ �����Դϴ�");
		return;
	}

	//���ؽ� ���̴��� �������, �ؽ�ó ���� ���͵��� ShaderResHelper�� �����Ѵ�
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	//�ȼ� ���̴��� �������, �ؽ�ó ���� ���͵��� ShaderResHelper�� �����Ѵ�
	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

}

