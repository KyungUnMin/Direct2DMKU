#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineVertex.h"

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEngineConstantBuffer.h"

#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

void GameEngineCore::CoreResourceInit()
{
	//쉐이더 파일의 시맨틱 문법을 위한 자료형 표현
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	//이때 쉐이더 파일에서 시맨틱 문법의 순서와 LayOut에 넣어주는 자료형 이름의 순서는 동일해야 한다


	//버텍스 버퍼 & 인덱스 버퍼 만들기
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, float4::Green };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, float4::Black };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, float4::White };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
	}
	
	{

		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// 앞면
		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		// 뒷면
		ArrVertex[4] = ArrVertex[0].RotationXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotationXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotationXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotationXDegReturn(180.0f);

		// 왼쪽면
		ArrVertex[8] = ArrVertex[0].RotationYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotationYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotationYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotationYDegReturn(90.0f);

		// 오른쪽
		ArrVertex[12] = ArrVertex[0].RotationYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotationYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotationYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotationYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotationXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotationXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotationXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotationXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotationXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotationXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotationXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotationXDegReturn(-90.0f);
	}

	
	//버텍스 쉐이더 컴파일
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResource");
		NewDir.Move("EngineResource");
		NewDir.Move("Shader");

		//해당 확장자를 가지고 있는 파일 가져오기
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl",".fx" });

		//일단 쉐이더 파일 하나만 컴파일하기
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
	}


	//래스터라이저 만들기
	{
		D3D11_RASTERIZER_DESC Decs = {};

		//D3D11_FILL_MODE
			// 채우기 모드
		//D3D11_CULL_MODE
			// 그리는 면
		//BOOL FrontCounterClockwise;
			// 시계방향이 앞면인지 뒷면인지 결정
		//INT DepthBias;
			//픽셀에 추가된 깊이 값
		//FLOAT DepthBiasClamp;
			// 픽셀의 최대 깊이 편향
		//FLOAT SlopeScaledDepthBias;
			// 거리에 따라 클리핑(이 물체를 기준으로 far가 1.0이 아니라 0.5로 자를 수 있음)
		//BOOL DepthClipEnable;
			// 화면 밖으로 빠져나가는 물체는 자르기(그리지 않음)
		//BOOL ScissorEnable;
			// 특정 영역만 그리기(근데 픽셀 쉐이더에서도 충분히 가능)
		//BOOL MultisampleEnable;
			//일반 안티에일리어싱 활성화 여부
		//BOOL AntialiasedLineEnable;
			// 선 앤티앨리어싱을 활성화 여부

		Decs.FillMode = D3D11_FILL_WIREFRAME;
		Decs.CullMode = D3D11_CULL_BACK;
		Decs.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("EngineBase", Decs);
	}


	//렌더링 파이프 라인 만들고 세팅하기
	{
		//랜더링 파이프라인은 자식에서 별도의 Create함수를 갖지 않는다
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

		//버텍스 버퍼 설정
		Pipe->SetVertexBuffer("Rect");
		Pipe->SetVertexShader("TextureShader.hlsl");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetRasterizer("EngineBase");
		Pipe->SetPixelShader("TextureShader.hlsl");
	}

}


void GameEngineCore::CoreResourceEnd()
{
	GameEngineRenderingPipeLine::ResourcesClear();

	GameEngineConstantBuffer::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();

	GameEngineMesh::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
}
