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

	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();
	if (nullptr == MainCamera)
	{
		MsgAssert("ī�޶� ����");
		return;
	}

	//ī�޶� ����Ŀ� ������� ����
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	Pipe->RenderingPipeLineSetting();

	//�ؽ�ó ����, ������� ���� ���� �̷������.
	ShaderResHelper.Setting();

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

	/*
	Copy�ϴ� ����
			���� ���ĸ� �� �� ���������� �ٸ� ����� �ؽ�ó�� �־��ֱ� ����
			�׷��� Copy�� ���� ���̴� ���ҽ� ���ۿ� �ִ� ���͵��� ����޴´�
			���̴� �ȿ� �ִ� ���ҽ����۴� ���÷����� �� � ���۵��� ����ߴ��� ���縸 �ϱ� ����
	*/

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


	//Ʈ������ ���� �ڵ����� �־��ֱ�(���̴� ���Ͽ� TransformData�� ���� ������۰� �־�߸� ��)
	if (true == ShaderResHelper.IsConstantBufferSetter("TransformData"))
	{
		const TransformData& Data= GetTransform()->GetTransDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
	
}

