#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include "TestLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::GameStart()
{
	new bool;

	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::ChangeLevel("TestLevel");
}

void ContentsCore::GameEnd()
{
}
