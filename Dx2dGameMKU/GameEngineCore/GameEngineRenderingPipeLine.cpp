#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{

}


//-------------REDERING---------


void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBuffer)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	VertexBuffer->Setting();
}

void GameEngineRenderingPipeLine::VertexShader()
{

}

void GameEngineRenderingPipeLine::InputAssembler2()
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
	VertexBuffer = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBuffer)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다");
	}
}
