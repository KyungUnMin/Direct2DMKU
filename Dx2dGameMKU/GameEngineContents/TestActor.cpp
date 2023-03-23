#include "TestActor.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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
	Radian += 100.f * _DeltaTime;

}

void TestActor::Render(float _DeltaTime)
{
	HDC Hdc = GameEngineWindow::GetWindowBackBufferHdc();

	const size_t Cnt = 4;

	POINT Point[Cnt];
	float4 Vertex[Cnt];
	Vertex[0] = { -0.5f, -0.5f, -0.5f };
	Vertex[1] = { 0.5f, -0.5f, -0.5f };
	Vertex[2] = { 0.5f, 0.5f, -0.5f };
	Vertex[3] = { -0.5f, 0.5f, -0.5f };

	/*Vertex[0] = float4(Vertex[0]).RotationYDeg(90.f);*/
	/*Vertex[1] = { 0.5f, -0.5f, -0.5f };
	Vertex[2] = { 0.5f, 0.5f, -0.5f };
	Vertex[3] = { -0.5f, 0.5f, -0.5f };*/

	
	
	for (size_t i = 0; i < Cnt; ++i)
	{
		Vertex[i] *= 100.f;
		Vertex[i].RotationZDeg(Radian);
		Vertex[i] += Offset;

		Point[i] = Vertex[i].ToWindowPOINT();
	}

	Polygon(Hdc, Point, Cnt);
}
