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
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineVertexShader.h"

void GameEngineCore::CoreResourceInit()
{

	//버텍스 버퍼 & 인덱스 버퍼 만들기
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f,0.0f }, float4::Red };
		ArrVertex[2] = { { 0.5f, -0.5f,0.0f }, float4::Red };
		ArrVertex[3] = { { -0.5f, -0.5f,0.0f }, float4::Red };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 3, 2 };

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
	}




	//렌더링 파이프 라인 만들고 세팅하기
	{
		//랜더링 파이프라인은 자식에서 별도의 Create함수를 갖지 않는다
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

		//버텍스 버퍼 설정
		Pipe->SetVertexBuffer("Rect");
		Pipe->SetVertexShader("TextureShader.hlsl");
		Pipe->SetIndexBuffer("Rect");
	}

}


void GameEngineCore::CoreResourceEnd()
{
	GameEngineResource<GameEngineRenderingPipeLine>::ResourcesClear();

	GameEngineResource<GameEngineVertexBuffer>::ResourcesClear();
	GameEngineResource<GameEngineVertexShader>::ResourcesClear();
	GameEngineResource<GameEngineIndexBuffer>::ResourcesClear();

	GameEngineResource<GameEngineMesh>::ResourcesClear();
	GameEngineResource<GameEngineTexture>::ResourcesClear();
	GameEngineResource<GameEngineRenderTarget>::ResourcesClear();
}
