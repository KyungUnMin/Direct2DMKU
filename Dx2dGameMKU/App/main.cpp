#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>

#include <GameEngineContents/RCG_GameCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <GameEngineContents/ContentsCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
	//GameEngineCore::Start(hInstance, RCG_GameCore::GameStart, RCG_GameCore::GameEnd);
}