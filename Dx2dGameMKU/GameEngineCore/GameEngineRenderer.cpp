#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::Render(float _DeltaTime)
{
	HDC Hdc = GameEngineWindow::GetWindowBackBufferHdc();

	const size_t Cnt = 24;

	POINT Point[Cnt];
	float4 Vertex[Cnt];

	{
		//�޸�
		Vertex[0] = { -0.5f, -0.5f, 0.5f };
		Vertex[1] = { 0.5f, -0.5f, 0.5f };
		Vertex[2] = { 0.5f, 0.5f, 0.5f };
		Vertex[3] = { -0.5f, 0.5f, 0.5f };

		//����
		Vertex[4] = Vertex[0].RotationYDegReturn(90.f);
		Vertex[5] = Vertex[1].RotationYDegReturn(90.f);
		Vertex[6] = Vertex[2].RotationYDegReturn(90.f);
		Vertex[7] = Vertex[3].RotationYDegReturn(90.f);

		//����
		Vertex[8] = Vertex[0].RotationYDegReturn(-90.f);
		Vertex[9] = Vertex[1].RotationYDegReturn(-90.f);
		Vertex[10] = Vertex[2].RotationYDegReturn(-90.f);
		Vertex[11] = Vertex[3].RotationYDegReturn(-90.f);

		//����
		Vertex[12] = Vertex[0].RotationXDegReturn(180.f);
		Vertex[13] = Vertex[1].RotationXDegReturn(180.f);
		Vertex[14] = Vertex[2].RotationXDegReturn(180.f);
		Vertex[15] = Vertex[3].RotationXDegReturn(180.f);

		//�Ʒ�
		Vertex[16] = Vertex[0].RotationXDegReturn(90.f);
		Vertex[17] = Vertex[1].RotationXDegReturn(90.f);
		Vertex[18] = Vertex[2].RotationXDegReturn(90.f);
		Vertex[19] = Vertex[3].RotationXDegReturn(90.f);

		//��
		Vertex[20] = Vertex[0].RotationXDegReturn(-90.f);
		Vertex[21] = Vertex[1].RotationXDegReturn(-90.f);
		Vertex[22] = Vertex[2].RotationXDegReturn(-90.f);
		Vertex[23] = Vertex[3].RotationXDegReturn(-90.f);
	}


	//ũ��
	GetTransform()->SetLocalScale(float4{ 100.f, 100.f, 100.f });

	const std::shared_ptr<GameEngineCamera>& MainCamera = GetLevel()->GetMainCamera();
	float4x4 ViewMatrix = MainCamera->GetView();
	float4x4 ProjectionMat = MainCamera->GetProjection();

	//ī�޶� ����
	GetTransform()->SetCameraMatrix(ViewMatrix, ProjectionMat);

	for (size_t i = 0; i < Cnt; ++i)
	{
		//�����Ʈ���� ����
		Vertex[i] = Vertex[i] * GetTransform()->GetWorldViewProjectionMatrixRef();

		//����
		Vertex[i] /= Vertex[i].w;
		Vertex[i].w = 1.0f;

		//����Ʈ ����
		Vertex[i] *= MainCamera->GetViewPort();

		Point[i] = Vertex[i].ToWindowPOINT();
	}

	for (size_t i = 0; i < 6; ++i)
	{
		size_t Index = i * 4;

		float4 V0 = Vertex[Index + 0];
		float4 V1 = Vertex[Index + 1];
		float4 V2 = Vertex[Index + 2];

		float4 Dir0 = V1 - V0;
		float4 Dir1 = V2 - V1;

		float4 Cross = float4::Cross3DReturn(Dir0, Dir1);
		if (0.f >= Cross.z)
			continue;

		Polygon(Hdc, &Point[Index], 4);
	}
}
