#include "GameEngineDebug.h"
// #include <iostream>
#include <crtdbg.h>

GameEngineDebug::GameEngineDebug()
{

}

GameEngineDebug::~GameEngineDebug()
{

}


void GameEngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameEngineDebug::LeakPointBreak(int _Value)
{
	_CrtSetBreakAlloc(_Value);
}
