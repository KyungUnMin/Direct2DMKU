#include "PrecompileHeader.h"
#include "TestLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

#include "TestActor.h"

void TestLevel::Start()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentsResource");
		NewDir.Move("ContentsResource");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		int a = 0;
	}



	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4{ 0.f, 0.f, -1000.f });

	CreateActor<TestActor>();

	//GameEngineDirectory Dir;
	//Dir.MoveParentToDirectory("ContentsResources");
	//Dir.Move("ContentsResources");



	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResource");
	Dir.Move("ContentsResource");
	std::string Path = Dir.GetPlusFileName("Bossintros_Yamada.avi").GetPathToString();
	/*Video = GameEngineVideo::Load(Path);
	Video->Play();*/

	GameEngineInput::CreateKey("VideoStop", VK_ESCAPE);
}

void TestLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	if (true == GetMainCamera()->IsFreeCamera())
		return;
	
	if (nullptr == Video)
		return;

	if (true == Video->IsFinished())
	{
		Video->Stop();
		Video = nullptr;
	}

	if (true == GameEngineInput::IsDown("VideoStop"))
	{
		Video->Stop();
		Video = nullptr;
	}
}
