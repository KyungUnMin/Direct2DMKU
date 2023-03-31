#include "TestActor.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

TestActor::TestActor()
{

}

TestActor::~TestActor()
{

}

void TestActor::Start()
{
}

void TestActor::Update(float _DeltaTime)
{

}

void TestActor::Render(float _DeltaTime)
{
	HDC Hdc = GameEngineWindow::GetWindowBackBufferHdc();

	const size_t Cnt = 24;

	POINT Point[Cnt];
	float4 Vertex[Cnt];

	{
		//뒷면
		Vertex[0] = { -0.5f, -0.5f, 0.5f };
		Vertex[1] = { 0.5f, -0.5f, 0.5f };
		Vertex[2] = { 0.5f, 0.5f, 0.5f };
		Vertex[3] = { -0.5f, 0.5f, 0.5f };

		//좌측
		Vertex[4] = Vertex[0].RotationYDegReturn(90.f);
		Vertex[5] = Vertex[1].RotationYDegReturn(90.f);
		Vertex[6] = Vertex[2].RotationYDegReturn(90.f);
		Vertex[7] = Vertex[3].RotationYDegReturn(90.f);

		//우측
		Vertex[8] = Vertex[0].RotationYDegReturn(-90.f);
		Vertex[9] = Vertex[1].RotationYDegReturn(-90.f);
		Vertex[10] = Vertex[2].RotationYDegReturn(-90.f);
		Vertex[11] = Vertex[3].RotationYDegReturn(-90.f);

		//앞측
		Vertex[12] = Vertex[0].RotationXDegReturn(180.f);
		Vertex[13] = Vertex[1].RotationXDegReturn(180.f);
		Vertex[14] = Vertex[2].RotationXDegReturn(180.f);
		Vertex[15] = Vertex[3].RotationXDegReturn(180.f);

		//아래
		Vertex[16] = Vertex[0].RotationXDegReturn(90.f);
		Vertex[17] = Vertex[1].RotationXDegReturn(90.f);
		Vertex[18] = Vertex[2].RotationXDegReturn(90.f);
		Vertex[19] = Vertex[3].RotationXDegReturn(90.f);

		//위
		Vertex[20] = Vertex[0].RotationXDegReturn(-90.f);
		Vertex[21] = Vertex[1].RotationXDegReturn(-90.f);
		Vertex[22] = Vertex[2].RotationXDegReturn(-90.f);
		Vertex[23] = Vertex[3].RotationXDegReturn(-90.f);
	}

	float4 Debug = GetTransform().GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform().GetLocalPosition();
	GetTransform().SetLocalScale(float4{ 100.f, 100.f, 100.f });
	//GetTransform().AddLocalRotation(float4{ 360.f * _DeltaTime,  360.f * _DeltaTime , 360.f * _DeltaTime });
	//GetTransform().SetLocalPosition(float4{ 100.f, 100.f });
	// 
	
	const std::shared_ptr<GameEngineCamera>& MainCamera = GetLevel()->GetMainCamera();
	float4x4 ViewMatrix = MainCamera->GetView();

	float4x4 LocalMax = GetTransform().GetLocalWorldMatrix();
	GetTransform().SetView(ViewMatrix);
	float4x4 WorldMat = GetTransform().GetWorldMatrix();

	//GetTransform().SetView(GetLevel()->GetMainCamera()->GetView());

	for (size_t i = 0; i < Cnt; ++i)
	{
		float4x4 WorldMat = GetTransform().GetWorldMatrixRef();
		Vertex[i] = Vertex[i] * GetTransform().GetWorldMatrixRef();
		//Vertex[i] = Vertex[i] * GetTransform().GetLocalWorldMatrixRef();
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
		if (0.f < Cross.z)
			continue;

		Polygon(Hdc, &Point[Index], 4);
	}
}





/*

HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// Rectangle(Dc, 0, 0, 100, 100);

	const int VertexCount = 24;

	float4 Pos = { 640, 360 };

	// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
	float4 ArrVertex[VertexCount];
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


	POINT ArrPoint[VertexCount];

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i] *= 100.f;
		ArrVertex[i].RotationXDeg(Radian);
		ArrVertex[i].RotationYDeg(Radian);
		ArrVertex[i].RotationZDeg(Radian);
		ArrVertex[i] += Pos;
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	for (size_t i = 0; i < 6; i++)
	{
		size_t Index = i * 4;

		float4 Vector0 = ArrVertex[Index + 0];
		float4 Vector1 = ArrVertex[Index + 1];
		float4 Vector2 = ArrVertex[Index + 2];

		float4 Dir0 = Vector0 - Vector1;
		float4 Dir1 = Vector1 - Vector2;

		float4 Cross = float4::CrossReturn(Dir0, Dir1);
		if (0 <= Cross.z)
		{
			continue;
		}

		Polygon(Dc, &ArrPoint[i * 4], 4);
	}

*/