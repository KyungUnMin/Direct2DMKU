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

	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();
	if (nullptr == MainCamera)
	{
		MsgAssert("카메라 없음");
		return;
	}

	//카메라 뷰행렬와 투영행렬 연산
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

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

