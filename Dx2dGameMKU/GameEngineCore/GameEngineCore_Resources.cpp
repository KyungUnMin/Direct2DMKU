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
	//���̴� ������ �ø�ƽ ������ ���� �ڷ��� ǥ��
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	//�̶� ���̴� ���Ͽ��� �ø�ƽ ������ ������ LayOut�� �־��ִ� �ڷ��� �̸��� ������ �����ؾ� �Ѵ�


	//���ؽ� ���� & �ε��� ���� �����
	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// �ո�
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
		NewDir.MoveParentToDirectory("EngineResource");
		NewDir.Move("EngineResource");
		NewDir.Move("Shader");

		//�ش� Ȯ���ڸ� ������ �ִ� ���� ��������
		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl",".fx" });

		//�ϴ� ���̴� ���� �ϳ��� �������ϱ�
		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
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

		Decs.FillMode = D3D11_FILL_WIREFRAME;
		Decs.CullMode = D3D11_CULL_BACK;
		Decs.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("EngineBase", Decs);
	}


	//������ ������ ���� ����� �����ϱ�
	{
		//������ ������������ �ڽĿ��� ������ Create�Լ��� ���� �ʴ´�
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

		//���ؽ� ���� ����
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
