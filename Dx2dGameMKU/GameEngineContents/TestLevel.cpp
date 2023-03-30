#include "TestLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCamera.h>

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

#include "TestActor.h"

void TestLevel::Loading()
{
	GetMainCamera()->GetTransform().SetLocalPosition(float4{ 0.f, 0.f, -100.f });

	CreateActor<TestActor>();

	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentsResources");
	//Dir.Move("ContentsResources");
}
