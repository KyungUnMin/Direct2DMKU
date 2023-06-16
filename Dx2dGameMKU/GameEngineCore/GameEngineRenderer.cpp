#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineMesh.h"
#include "GameEngineInputLayOut.h"


GameEngineRenderUnit::GameEngineRenderUnit()
{
	//���� ���鶧 ��ǲ ���̾ƿ� ����, (���� ������ ���� ����)
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>();
}

void GameEngineRenderUnit::SetMesh(const std::string_view& _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if ((false == InputLayOutPtr->IsCreate()) && (nullptr != Pipe))
	{
		//���ؽ� ���ۿ� ���ؽ� ���̴��� �������� �������� ��ǲ ���̾ƿ� ����
		InputLayOutPtr->ResCreate(Mesh->GetVertexBuffer(), Pipe->GetVertexShader());
	}
}


void GameEngineRenderUnit::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	/*
	Copy�ϴ� ����
			���� ���ĸ� �� �� ���������� �ٸ� ����� �ؽ�ó�� �־��ֱ� ����
			�׷��� Copy�� ���� ���̴� ���ҽ� ���ۿ� �ִ� ���͵��� ����޴´�
			���̴� �ȿ� �ִ� ���ҽ����۴� ���÷����� �� � ���۵��� ����ߴ��� ���縸 �ϱ� ����
	*/

	//���ؽ� ���̴� ���� �޾ƿ���
	//���ؽ� ���̴��� �������, �ؽ�ó ���� ���͵��� ShaderResHelper�� �����Ѵ�
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	//�ȼ� ���̴� ���� �޾ƿ���
	//�ȼ� ���̴��� �������, �ؽ�ó ���� ���͵��� ShaderResHelper�� �����Ѵ�
	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	//�޽� ������ ���ؽ� ���ۿ� �������� ���ؽ� ���̴��� �������� ��ǲ ���̾ƿ� ����
	if ((false == InputLayOutPtr->IsCreate()) && (nullptr != Mesh))
	{
		InputLayOutPtr->ResCreate(Mesh->GetVertexBuffer(), Pipe->GetVertexShader());
	}
}



void GameEngineRenderUnit::Render(float _DeltaTime)
{
	if (nullptr == Mesh)
	{
		MsgAssert("�Ž��� �������� �ʴ� ����Ʈ �Դϴ�");
		return;
	}

	if (nullptr == Pipe)
	{
		MsgAssert("������������ �������� �ʴ� ����Ʈ �Դϴ�");
		return;
	}

	InputLayOutPtr->Setting();

	//��ǲ �����1�� ��ǲ �����2 ������ ����
	Mesh->Setting();

	//GPU�� ������ ���������� �ܰ迡 ���� �ʿ��� ���� ����
	Pipe->RenderingPipeLineSetting();

	//GPU�� ���̴� ������ ����(������۳� �ؽ�ó ���� ����)
	ShaderResHelper.Setting();

	//�׸���
	//Pipe->Render();

	//���������� �׸��� �ܰ�(�׸��� ����� ������������ �� �� �� �ε������۸� �̿��ؼ� �׸� ��)
	UINT IndexCount = Mesh->IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
}



GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	//���� ī�޶� ���
	PushCameraRender(0);
}



void GameEngineRenderer::RenderTransformUpdate(GameEngineCamera* _Camera)
{
	if (nullptr == _Camera)
	{
		MsgAssert("ī�޶� nullptr�Դϴ�");
		return;
	}

	//ī�޶� ����Ŀ� ������� ����
	GetTransform()->SetCameraMatrix(_Camera->GetView(), _Camera->GetProjection());
}



void GameEngineRenderer::Render(float _DeltaTime)
{
	for (size_t i = 0; i < Units.size(); ++i)
	{
		Units[i]->Render(_DeltaTime);
	}
}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLine(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("�������� �ʴ� ���� ����Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	return Units[_index]->Pipe;
}


std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLineClone(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("�������� �ʴ� ���� ����Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	//Ŭ���� �ȵ� ���������θ�
	if (false == Units[_index]->Pipe->IsClone())
	{
		//������ �Ȱ��� ������������ �����Ѵ�
		Units[_index]->Pipe = Units[_index]->Pipe->Clone();
	}

	return Units[_index]->Pipe;
}


void GameEngineRenderer::SetMesh(const std::string_view& _Name, int _index /*= 0*/)
{
	if (Units.size() + 1 <= _index)
	{
		MsgAssert("�ʹ�ū ��������Ʈ Ȯ���� �Ϸ��� �߽��ϴ�");
		return;
	}

	//���� �������� �ʴ� �����̶�� ������ Ȯ��
	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}


	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];
	if (nullptr == Unit)
	{
		MsgAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	//�޽� ���
	Unit->Mesh = GameEngineMesh::Find(_Name);
}



void GameEngineRenderer::SetPipeLine(const std::string_view& _Name, int _index /*= 0*/)
{
	//_index�� �Ѱ����� �������Ѽ� Ȯ���� �� ����
	if (Units.size() + 1 <= _index)
	{
		MsgAssert("�ʹ�ū ��������Ʈ Ȯ���� �Ϸ��� �߽��ϴ�");
		return;
	}

	//���� ���� ����
	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}


	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];
	if (nullptr == Unit)
	{
		MsgAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	Unit->SetPipeLine(_Name);
	if (nullptr == Unit->Pipe)
	{
		MsgAssert("�������� �ʴ� �̸��� ������ ������ �����Դϴ�");
		return;
	}


	//Ʈ������ ���� �ڵ����� �־��ֱ�(���̴� ���Ͽ� TransformData�� ���� ������۰� �־�߸� ��)
	if (true == Unit->ShaderResHelper.IsConstantBufferSetter("TransformData"))
	{
		const TransformData& Data= GetTransform()->GetTransDataRef();
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
	
}


void GameEngineRenderer::PushCameraRender(int _CameraOrder)
{
	GetLevel()->PushCameraRenderer(DynamicThis<GameEngineRenderer>(), _CameraOrder);
}

void GameEngineRenderer::CalSortZ(GameEngineCamera* _Camera)
{
	// ī�޶� �������� �� ��ǥ�� �������� ����Ѵ�
	switch (_Camera->ProjectionType)
	{
	case CameraType::Orthogonal:
	{
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.z;
		break;
	}
	case CameraType::Perspective:
	{
		float4 View = GetTransform()->GetWorldPosition() * _Camera->View;
		CalZ = View.Size();
		break;
	}
	default:
		break;
	}


}
