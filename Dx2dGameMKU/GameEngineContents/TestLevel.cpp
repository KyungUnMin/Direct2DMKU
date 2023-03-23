#include "TestLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineResource.h>

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

#include "TestActor.h"

void TestLevel::Loading()
{
	CreateActor<TestActor>();

	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentsResources");
	//Dir.Move("ContentsResources");
}
