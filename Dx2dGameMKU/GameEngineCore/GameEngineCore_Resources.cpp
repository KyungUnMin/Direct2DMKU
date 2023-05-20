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
	//�ؽ�ó �ε�
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


	//���̴� ������ �ø�ƽ ������ ���� �ڷ��� ǥ��
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);
	//�̶� ���̴� ���Ͽ��� �ø�ƽ ������ ������ LayOut�� �־��ִ� �ڷ��� �̸��� ������ �����ؾ� �Ѵ�


	//������ ���÷��� ���̴� �ε��ϱ� ���� ������ ��(�������� �������ִ� �⺻ ���÷�)
	{
		//Ŭ���� ���÷�
		D3D11_SAMPLER_DESC SamplerData = {};

		SamplerData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		// �ؽ�ó�� �ָ������� �������� -> �ȹ�����.
		SamplerData.MipLODBias = 0.0f;
		SamplerData.MaxAnisotropy = 1;
		SamplerData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamplerData.MinLOD = -FLT_MAX;
		SamplerData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("CLAMPSAMPLER", SamplerData);
	}

	{
		//�� ���÷�
		D3D11_SAMPLER_DESC SamplerData = {};

		SamplerData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		// �ؽ�ó�� �ָ������� �������� -> �ȹ�����.
		SamplerData.MipLODBias = 0.0f;
		SamplerData.MaxAnisotropy = 1;
		SamplerData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamplerData.MinLOD = -FLT_MAX;
		SamplerData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAPSAMPLER", SamplerData);
	}


	//���ؽ� ���� & �ε��� ���� �����
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// �ո�
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);
	}


	//������(ī�޶� ��) ���ؽ� ���� & �ε��� ���� �����
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);

		//Ư���� ��� ���� ȭ���� �ٷ� ���� ä��� ���� ������ -1 ~ 1�� ����
		//(������ȯ�� ������ -1 ~ 1�� ��ҵǱ� ����)
		ArrVertex[0] = { { -1.0f, 1.0f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 1.0f, 1.0f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 1.0f, -1.0f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -1.0f, -1.0f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("FullRect", ArrVertex);
		GameEngineIndexBuffer::Create("FullRect", ArrIndex);

	}



	//���� �����
	{
		D3D11_BLEND_DESC Desc = { 0, };

		//�ڵ����� ���ĺκ��� �����ϴ���(������ false)
		Desc.AlphaToCoverageEnable = false;
		//����Ÿ�ٵ� ���� �������� ������ �����ϴ���(false�� ������ 0�� ������)
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		//����(RGBA) ���� ����ũ ���� ����?
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;



		//�� ���� ȥ�� (Op�� ���۷��̼��� �ǹ�)
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		//���İ��� ȥ��
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		//���� = (SrcAlpha * SrcBlendAlpha) BlendOpAlpha (DestAlpha * DestBlendAlpha)

		GameEngineBlend::Create("AlphaBlend", Desc);
	}
	

	//���� ����
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };

		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("EngineDepth", Desc);
	}


	//������(ī�޶� ��) ����
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;

		//�׻� ������ �ȴ�
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;

		GameEngineDepthState::Create("AlwayDepth", Desc);
	}



	{

		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// �ո�
		ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
		ArrVertex[1] = { 0.5f, -0.5f,0.5f };
		ArrVertex[2] = { 0.5f, 0.5f,0.5f };
		ArrVertex[3] = { -0.5f, 0.5f,0.5f };

		// �޸�
		ArrVertex[4] = ArrVertex[0].RotationXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotationXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotationXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotationXDegReturn(180.0f);

		// ���ʸ�
		ArrVertex[8] = ArrVertex[0].RotationYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotationYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotationYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotationYDegReturn(90.0f);

		// ������
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

	
	//���ؽ� ���̴� ������
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		//�ش� Ȯ���ڸ� ������ �ִ� ���� ��������
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl",".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Merge_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Merge_PS");

		GameEngineVertexShader::Load(Files[1].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[1].GetFullPath(), "Texture_PS");
	}


	//�����Ͷ����� �����
	{
		D3D11_RASTERIZER_DESC Decs = {};

		//D3D11_FILL_MODE
			// ä��� ���
		//D3D11_CULL_MODE
			// �׸��� ��
		//BOOL FrontCounterClockwise;
			// �ð������ �ո����� �޸����� ����
		//INT DepthBias;
			//�ȼ��� �߰��� ���� ��
		//FLOAT DepthBiasClamp;
			// �ȼ��� �ִ� ���� ����
		//FLOAT SlopeScaledDepthBias;
			// �Ÿ��� ���� Ŭ����(�� ��ü�� �������� far�� 1.0�� �ƴ϶� 0.5�� �ڸ� �� ����)
		//BOOL DepthClipEnable;
			// ȭ�� ������ ���������� ��ü�� �ڸ���(�׸��� ����)
		//BOOL ScissorEnable;
			// Ư�� ������ �׸���(�ٵ� �ȼ� ���̴������� ����� ����)
		//BOOL MultisampleEnable;
			//�Ϲ� ��Ƽ���ϸ���� Ȱ��ȭ ����
		//BOOL AntialiasedLineEnable;
			// �� ��Ƽ�ٸ������ Ȱ��ȭ ����

		//Decs.FillMode = D3D11_FILL_WIREFRAME;
		Decs.CullMode = D3D11_CULL_NONE;
		Decs.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Decs);
	}


	//������ ������ ���� ����� �����ϱ�
	{
		//������ ������������ �ڽĿ��� ������ Create�Լ��� ���� �ʴ´�
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetVertexShader("TextureShader.hlsl");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("TextureShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	//������(ī�޶� ��) ������ ������ ���� ����� �����ϱ�
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
