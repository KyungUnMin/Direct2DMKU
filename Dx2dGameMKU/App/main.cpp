#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>
#include <GameEngineBase/GameEngineMath.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

//����׸� �ڸ����� �� �ߴµ� ��� �ٸ� �ܺ� ���� lib�� ����� �� ������?
//�Ƹ�����

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	float4x4 Proj;
	Proj.PersperctiveFovLH(60.f, 1280.f / 720.f);
	float4 Test = { 0.f, -500.f, 5000.f };

	Test *= Proj;
	Test.x /= Test.w;
	Test.y /= Test.w;
	Test.z /= Test.w;

	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}