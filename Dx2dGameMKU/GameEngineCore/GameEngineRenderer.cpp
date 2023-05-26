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
	for (size_t i = 0; i < Units.size(); ++i)
	{
		Units[i]->Pipe->RenderingPipeLineSetting();

		//텍스처 세팅, 상수버퍼 세팅 등이 이루어진다.
		Units[i]->ShaderResHelper.Setting();

		Units[i]->Pipe->Render();
	}
	
}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLine(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	return Units[_index]->Pipe;
}


std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderer::GetPipeLineClone(int _index/* = 0*/)
{
	if (Units.size() <= _index)
	{
		MsgAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	//클론이 안된 파이프라인만
	if (false == Units[_index]->Pipe->IsClone())
	{
		//별도의 똑같은 파이프라인을 생성한다
		Units[_index]->Pipe = Units[_index]->Pipe->Clone();
	}

	return Units[_index]->Pipe;
}



void GameEngineRenderer::SetPipeLine(const std::string_view& _Name, int _index /*= 0*/)
{
	//_index를 한개씩만 증가시켜서 확장할 수 있음
	if (Units.size() + 1 <= _index)
	{
		MsgAssert("너무큰 랜더유니트 확장을 하려고 했습니다");
		return;
	}

	//렌더 유닛 생성
	if (Units.size() <= _index)
	{
		Units.resize(_index + 1);
		Units[_index] = std::make_shared<GameEngineRenderUnit>();
	}


	std::shared_ptr<GameEngineRenderUnit> Unit = Units[_index];
	if (nullptr == Unit)
	{
		MsgAssert("존재하지 않는 랜더유니트를 사용하려고 했습니다.");
		return;
	}


	Unit->Pipe = GameEngineRenderingPipeLine::Find(_Name);
	if (nullptr == Unit->Pipe)
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
		const GameEngineShaderResHelper& Res = Unit->Pipe->GetVertexShader()->GetShaderResHelper();
		Unit->ShaderResHelper.Copy(Res);
	}

	//픽셀 쉐이더의 상수버퍼, 텍스처 등의 세터들을 ShaderResHelper에 저장한다
	{
		const GameEngineShaderResHelper& Res = Unit->Pipe->GetPixelShader()->GetShaderResHelper();
		Unit->ShaderResHelper.Copy(Res);
	}


	//트랜스폼 정보 자동으로 넣어주기(쉐이더 파일에 TransformData와 같은 상수버퍼가 있어야만 함)
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
	// 카메라를 원점으로 한 좌표를 기준으로 계산한다
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
