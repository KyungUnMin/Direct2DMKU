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
		MsgAssert("인풋 레이아웃이 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	InputLayOutPtr->Setting();

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
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);

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
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("래스터라이저가 존재하지 않아서 세팅이 불가능합니다");
		return;
	}

	//레스터 라이저 단계에서는 색상 뿐만 아니라 위치도 선형보간 된다
	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("픽셀 쉐이더가 존재하지 않아서 픽셀 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	PixelShaderPtr->Setting();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	//여기서 설정하지 않고 GameEngineDevice::RenderStart에서 백버퍼 렌더타겟을 이용해 설정
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

	//버텍스 버퍼와 버텍스 쉐이더가 모두 만들어 졌을때 인풋 레이아웃을 만든다
	//(인풋 레이아웃은 버텍스 버퍼가 들고 있는 버텍스의 레이아웃 정보와 
	// 쉐이더 파일의 바이너리 코드 정보를 필요로 하기 때문이다)
	if (nullptr == VertexShaderPtr)
		return;

	//인풋 레이아웃 생성
	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}



void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다");
	}

	//버텍스 버퍼와 버텍스 쉐이더가 모두 만들어 졌을때 인풋 레이아웃을 만든다
	//(인풋 레이아웃은 버텍스 버퍼가 들고 있는 버텍스의 레이아웃 정보와 
	// 쉐이더 파일의 바이너리 코드 정보를 필요로 하기 때문이다)
	if (nullptr == VertexBufferPtr)
		return;

	//인풋 레이아웃 생성
	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
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

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("존재하지 않는 레스터라이저를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value) 
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("존재하지 않는 픽셀 쉐이더를 사용하려고 했습니다.");
	}
}



void GameEngineRenderingPipeLine::Render()
{
	//GPU에 랜더링 파이프 라인을 세팅하는 단계들
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


	//실질적으로 그리는 단계(그리는 방법이 여러가지지만 그 중 꼭 인덱스버퍼를 이용해서 그릴 것)
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
}
