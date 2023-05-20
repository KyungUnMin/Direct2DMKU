#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineResource.h"
#include "GameEngineShaderResHelper.h"

#include "GameEngineVertex.h"

#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthState.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderingPipeLine.h"



void GameEngineCore::CoreResourceInit()
{
	//텍스처 로드
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); ++i)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

	}


	//쉐이더 파일의 시맨틱 문법을 위한 자료형 표현
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);
	//이때 쉐이더 파일에서 시맨틱 문법의 순서와 LayOut에 넣어주는 자료형 이름의 순서는 동일해야 한다


	//구조상 샘플러는 쉐이더 로드하기 전에 만들어야 함(엔진에서 지원해주는 기본 샘플러)
	{
		//클램프 샘플러
		D3D11_SAMPLER_DESC SamplerData = {};

		SamplerData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		// 텍스처가 멀리있을때 뭉갤꺼냐 -> 안뭉갠다.
		SamplerData.MipLODBias = 0.0f;
		SamplerData.MaxAnisotropy = 1;
		SamplerData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamplerData.MinLOD = -FLT_MAX;
		SamplerData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("CLAMPSAMPLER", SamplerData);
	}

	{
		//랩 샘플러
		D3D11_SAMPLER_DESC SamplerData = {};

		SamplerData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		// 텍스처가 멀리있을때 뭉갤꺼냐 -> 안뭉갠다.
		SamplerData.MipLODBias = 0.0f;
		SamplerData.MaxAnisotropy = 1;
		SamplerData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamplerData.MinLOD = -FLT_MAX;
		SamplerData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAPSAMPLER", SamplerData);
	}


	//버텍스 버퍼 & 인덱스 버퍼 만들기
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
	}


	//머지용(카메라 용) 버텍스 버퍼 & 인덱스 버퍼 만들기
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);

		//특별한 계산 없이 화면을 바로 가득 채우기 위해 범위를 -1 ~ 1로 맞춤
		//(투영변환시 범위가 -1 ~ 1로 축소되기 때문)
		ArrVertex[0] = { { -1.0f, 1.0f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 1.0f, 1.0f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 1.0f, -1.0f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -1.0f, -1.0f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("FullRect", ArrVertex);
		GameEngineIndexBuffer::Create("FullRect", ArrIndex);

	}



	//블렌드 만들기
	{
		D3D11_BLEND_DESC Desc = { 0, };

		//자동으로 알파부분을 제거하는지(느려서 false)
		Desc.AlphaToCoverageEnable = false;
		//렌더타겟들 마다 여러개의 블렌더를 세팅하는지(false면 무조껀 0번 블렌더로)
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		//모든색(RGBA) 블렌드 마스크 사용시 적용?
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;



		//두 색을 혼합 (Op는 오퍼레이션을 의미)
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		//알파값을 혼합
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		//알파 = (SrcAlpha * SrcBlendAlpha) BlendOpAlpha (DestAlpha * DestBlendAlpha)

		GameEngineBlend::Create("AlphaBlend", Desc);
	}
	

	//깊이 버퍼
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };

		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("EngineDepth", Desc);
	}


	//머지용(카메라 용) 뎁스
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;

		//항상 덮어씌우게 된다
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("AlwayDepth", Desc);
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
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		//해당 확장자를 가지고 있는 파일 가져오기
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl",".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Merge_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Merge_PS");

		GameEngineVertexShader::Load(Files[1].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[1].GetFullPath(), "Texture_PS");
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

		//Decs.FillMode = D3D11_FILL_WIREFRAME;
		Decs.CullMode = D3D11_CULL_NONE;
		Decs.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Decs);
	}


	//렌더링 파이프 라인 만들고 세팅하기
	{
		//랜더링 파이프라인은 자식에서 별도의 Create함수를 갖지 않는다
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetVertexShader("TextureShader.hlsl");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("TextureShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	//머지용(카메라 용) 렌더링 파이프 라인 만들고 세팅하기
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("Merge");
		Pipe->SetVertexBuffer("FullRect");
		Pipe->SetIndexBuffer("FullRect");
		Pipe->SetVertexShader("MergeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("MergeShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("AlwayDepth");

		//
		GameEngineRenderTarget::RenderTargetUnitInit();
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
	GameEngineBlend::ResourcesClear();
	GameEngineDepthState::ResourcesClear();
}
