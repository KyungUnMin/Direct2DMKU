#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

//프라그마 코멘츠를 안 했는데 어떻게 다른 외부 포함 lib를 사용할 수 있을까?
//아모른직다

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}