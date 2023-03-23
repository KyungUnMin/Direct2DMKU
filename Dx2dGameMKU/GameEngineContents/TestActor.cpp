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
	Radian += _DeltaTime * 360.f;
}

void TestActor::Render(float _DeltaTime)
{
	HDC hDC = GameEngineWindow::GetWindowBackBufferHdc();

	const int VertexCnt = 4;
	POINT Vetexs[VertexCnt];
	std::vector<float4> Points(VertexCnt);

	Points[0] = { -0.5f, -0.5f, 0.5f };
	Points[1] = { 0.5f, -0.5f,0.5f };
	Points[2] = { 0.5f, 0.5f,0.5f };
	Points[3] = { -0.5f, 0.5f,0.5f };

	for (size_t i = 0; i < VertexCnt; ++i)
	{
		Points[i] *= 100.f;
		//Points[i].RotationXDeg(Radian);
		Points[i].RotationYDeg(Radian);
		Points[i].RotationZDeg(Radian);
		Points[i] += Offset;
		Vetexs[i] = Points[i].ToWindowPOINT();
	}

	Polygon(hDC, Vetexs, VertexCnt);
}
