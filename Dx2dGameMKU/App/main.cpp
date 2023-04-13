#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>
#include <GameEngineBase/GameEngineMath.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	

	float4x4 Parent;

	Parent.ArrVector[3] = { -100, -100 };
	Parent.Arr2D[0][0] = 2.0f;
	Parent.Arr2D[1][1] = 2.0f;

	float4 LocalPostion = { 100, 100 };
	float4 WorldPostion = { 300, 300 };

	float4 LocalScale = { 2, 2, 0.0f, 0.0f };
	float4 WorldScale = { 2, 2, 0.0f, 0.0f };

	float4 LocalPostionValue = WorldPostion * Parent.InverseReturn();
	float4 WorldPostionValue = LocalPostion * Parent;

	float4 LocalScaleValue = WorldScale * Parent.InverseReturn();
	float4 WorldScaleValue = LocalScale * Parent;


	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}