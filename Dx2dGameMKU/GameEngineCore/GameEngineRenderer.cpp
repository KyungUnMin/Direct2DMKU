#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"



void GameEngineRenderUnit::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	//버텍스 쉐이더 정보 받아오기
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}

	//픽셀 쉐이더 정보 받아오기
	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res);
	}
}



void GameEngineRenderUnit::Render(float _DeltaTime)
{
	//GPU에 렌더링 파이프라인 단계에 따라 필요한 정보 설정
	Pipe->RenderingPipeLineSetting();
	//GPU에 쉐이더 정보를 설정(상수버퍼나 텍스처 같은 정보)
	ShaderResHelper.Setting();
	//그리기
	Pipe->Render();
}



GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Start()
{
	//메인 카메라에 등록
	PushCameraRender(0);
}



void GameEngineRenderer::RenderTransformUpdate(GameEngineCamera* _Camera)
{
	if (nullptr == _Camera)
	{
		MsgAssert("카메라가 nullptr입니다");
		return;
	}

	//카메라 뷰행렬와 투영행렬 연산
	GetTransform()->SetCameraMatrix(_Camera->GetView(), _Camera->GetProjection());
}



void GameEngineRenderer::Render(float _DeltaTime)
{
	if (nullptr == Pipe)
	{
		MsgAssert("아직 렌더러에 렌더링 파이프라인을 설정해주지 않았습니다");
		return;
	}

	Pipe->RenderingPipeLineSetting();

	//텍스처 세팅, 상수버퍼 세팅 등이 이루어진다.
	ShaderResHelper.Setting();

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

	/*
	Copy하는 이유
			같은 랜파를 쓸 때 랜더러마다 다른 상수나 텍스처를 넣어주기 위함
			그래서 Copy를 통해 쉐이더 리소스 헬퍼에 있는 세터들을 복사받는다
			쉐이더 안에 있는 리소스헬퍼는 리플렉션할 때 어떤 버퍼들을 사용했는지 조사만 하기 위함
	*/

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


	//트랜스폼 정보 자동으로 넣어주기(쉐이더 파일에 TransformData와 같은 상수버퍼가 있어야만 함)
	if (true == ShaderResHelper.IsConstantBufferSetter("TransformData"))
	{
		const TransformData& Data= GetTransform()->GetTransDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
	
}


void GameEngineRenderer::PushCameraRender(int _CameraOrder)
{
	GetLevel()->PushCameraRenderer(DynamicThis<GameEngineRenderer>(), _CameraOrder);
}