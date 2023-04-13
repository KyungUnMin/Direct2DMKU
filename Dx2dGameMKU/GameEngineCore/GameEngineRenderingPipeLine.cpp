#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}


//-------------REDERING---------


void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBufferPtr->Setting();
}

void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않아서 버텍스쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	VertexShaderPtr->Setting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("인덱스 버퍼가 존재하지 않아서 인풋어셈블러2 과정을 실행할 수 없습니다.");
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

}

void GameEngineRenderingPipeLine::PixelShader()
{

}

void GameEngineRenderingPipeLine::OutputMerger()
{

}


//-------------REDERING---------


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다");
	}
}

void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("존재하지 않는 인덱스 버퍼를 사용하려고 했습니다");
	}
}




void GameEngineRenderingPipeLine::Render()
{
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
