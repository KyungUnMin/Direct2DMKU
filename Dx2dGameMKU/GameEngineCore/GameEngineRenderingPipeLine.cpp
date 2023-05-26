#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineDepthState.h"


GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>();
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}


//-------------REDERING---------


void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == InputLayOutPtr)
	{
		MsgAssert("��ǲ ���̾ƿ��� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	InputLayOutPtr->Setting();

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	VertexBufferPtr->Setting();
}

void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʾƼ� ���ؽ����̴� ������ ������ �� �����ϴ�.");
		return;
	}

	VertexShaderPtr->Setting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�ε��� ���۰� �������� �ʾƼ� ��ǲ�����2 ������ ������ �� �����ϴ�.");
		return;
	}

	IndexBufferPtr->Setting();

	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}


void GameEngineRenderingPipeLine::HullShader()
{
}
void GameEngineRenderingPipeLine::Tesselator()
{
}
void GameEngineRenderingPipeLine::DomainShader()
{
}
void GameEngineRenderingPipeLine::GeometryShader() 
{
}


void GameEngineRenderingPipeLine::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�����Ͷ������� �������� �ʾƼ� ������ �Ұ����մϴ�");
		return;
	}

	//������ ������ �ܰ迡���� ���� �Ӹ� �ƴ϶� ��ġ�� �������� �ȴ�
	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʾƼ� �ȼ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	PixelShaderPtr->Setting();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	if (nullptr == BlendStatePtr)
	{
		MsgAssert("���尡 �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
		return;
	}

	BlendStatePtr->Setting();

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("���� ���ٽ� ������Ʈ�� �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
		return;
	}

	DepthStatePtr->Setting();

	//GameEngineDevice::RenderStart���� ����� ����Ÿ���� �̿��� �׷��� RTV ����
	//���� ���� ���ٽǿ� ���� ���̹��� �ؽ�ó�� GameEngineDevice�� �ִ� RTV�� Setting �Լ����� �����ȴ�
}


//-------------REDERING---------


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�");
	}

	//���ؽ� ���ۿ� ���ؽ� ���̴��� ��� ����� ������ ��ǲ ���̾ƿ��� �����
	//(��ǲ ���̾ƿ��� ���ؽ� ���۰� ��� �ִ� ���ؽ��� ���̾ƿ� ������ 
	// ���̴� ������ ���̳ʸ� �ڵ� ������ �ʿ�� �ϱ� �����̴�)
	if (nullptr == VertexShaderPtr)
		return;

	//��ǲ ���̾ƿ� ����
	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}



void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���̴��� ����Ϸ��� �߽��ϴ�");
	}

	//���ؽ� ���ۿ� ���ؽ� ���̴��� ��� ����� ������ ��ǲ ���̾ƿ��� �����
	//(��ǲ ���̾ƿ��� ���ؽ� ���۰� ��� �ִ� ���ؽ��� ���̾ƿ� ������ 
	// ���̴� ������ ���̳ʸ� �ڵ� ������ �ʿ�� �ϱ� �����̴�)
	if (nullptr == VertexBufferPtr)
		return;

	//��ǲ ���̾ƿ� ����
	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}

void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�������� �ʴ� �ε��� ���۸� ����Ϸ��� �߽��ϴ�");
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�������� �ʴ� �����Ͷ������� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�������� �ʴ� �ȼ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetBlendState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	BlendStatePtr = GameEngineBlend::Find(UpperName);

	if (nullptr == BlendStatePtr)
	{
		MsgAssert("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetDepthState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	DepthStatePtr = GameEngineDepthState::Find(UpperName);

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("�������� �ʴ� ���� ���� ������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}
}



void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	//GPU�� ������ ������ ������ �����ϴ� �ܰ��
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	HullShader();
	Tesselator();
	DomainShader();
	GeometryShader();
	Rasterizer();
	PixelShader();
	OutputMerger();
}

void GameEngineRenderingPipeLine::Render()
{
	//���������� �׸��� �ܰ�(�׸��� ����� ������������ �� �� �� �ε������۸� �̿��ؼ� �׸� ��)
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderingPipeLine::Clone()
{
	std::shared_ptr<GameEngineRenderingPipeLine> ClonePipe = std::make_shared<GameEngineRenderingPipeLine>();

	ClonePipe->InputLayOutPtr = InputLayOutPtr;
	ClonePipe->VertexBufferPtr = VertexBufferPtr;
	ClonePipe->IndexBufferPtr = IndexBufferPtr;
	ClonePipe->VertexShaderPtr = VertexShaderPtr;
	ClonePipe->RasterizerPtr = RasterizerPtr;
	ClonePipe->PixelShaderPtr = PixelShaderPtr;
	ClonePipe->BlendStatePtr = BlendStatePtr;
	ClonePipe->DepthStatePtr = DepthStatePtr;
	ClonePipe->IsCloneValue = true;

	return ClonePipe;
}
