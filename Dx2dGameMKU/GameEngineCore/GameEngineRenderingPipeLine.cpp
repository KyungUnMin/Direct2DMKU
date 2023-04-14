#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineInputLayOut.h"


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
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�ε��� ���۰� �������� �ʾƼ� ��ǲ�����2 ������ ������ �� �����ϴ�.");
		return;
	}

	IndexBufferPtr->Setting();
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
	//���⼭ �������� �ʰ� GameEngineDevice::RenderStart���� ����� ����Ÿ���� �̿��� ����
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



void GameEngineRenderingPipeLine::Render()
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


	//���������� �׸��� �ܰ�(�׸��� ����� ������������ �� �� �� �ε������۸� �̿��ؼ� �׸� ��)
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
}
