#include "TestLevel.h"
#include <GameEngineBase/GameEngineDebug.h>

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
}
