#include <Windows.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>

#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineSerializer Data;
	Data.Write(10);

	GameEngineFile NewFile = GameEngineFile("C:\\AROCK\\AAAA.txt");
	NewFile.Save(Data);
}