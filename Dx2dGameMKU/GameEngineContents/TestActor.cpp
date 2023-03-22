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
	//Radian += _DeltaTime * 360.f;
}

void TestActor::Render(float _DeltaTime)
{
	HDC hDC = GameEngineWindow::GetWindowBackBufferHdc();

	const int VertexCnt = 4;
	POINT Vetexs[VertexCnt];
	std::vector<float4> Points(VertexCnt);

	Points[0] = { -50.f, -50.f };
	Points[1] = { 50.f, -50.f };
	Points[2] = { 50.f, 50.f };
	Points[3] = { -50.f, 50.f };

	for (size_t i = 0; i < VertexCnt; ++i)
	{
		Points[i].RotationZDeg(45.f);
		//Points[i] += Offset;
		Vetexs[i] = Points[i].ToWindowPOINT();
	}

	Polygon(hDC, Vetexs, VertexCnt);
}
