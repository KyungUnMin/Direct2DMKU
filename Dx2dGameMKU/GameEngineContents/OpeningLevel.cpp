#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "OpeningActor.h"

OpeningLevel::OpeningLevel()
{

}

OpeningLevel::~OpeningLevel()
{

}

#include <GameEngineCore/GameEngineVideo.h>

void OpeningLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Video);
		Dir.Move("Opening");
		std::vector<GameEngineFile>Files = Dir.GetAllFile({ ".avi" });

		for (const GameEngineFile& File : Files)
		{
			GameEngineVideo::Load(File.GetFullPath());
		}

		Video1 = GameEngineVideo::Find("ArcCI_Final_6sec_com_reg_TEST20.avi");
		Video2 = GameEngineVideo::Find("WF_Logo_2016.avi");

		//Video1->Play();
	}






	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Opening");

	std::vector<GameEngineFile> Images = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& Path : Images)
	{
		GameEngineTexture::Load(Path.GetFullPath());
	}

	CreateActor<OpeningActor>();
}

#include "KeyMgr.h"

void OpeningLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		Video2->Play();
	}

	//GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	//if (nullptr != Video1 && GameEngineVideo::VideoState::UNKNOWN == State)
	//{
	//	//Video1->Stop();
	//	Video1 = nullptr;
	//	Video2->Play();
	//	return;
	//}

	//if (nullptr != Video1)
	//	return;

	//if (nullptr != Video2 && GameEngineVideo::VideoState::UNKNOWN == State)
	//{
	//	//Video2->Stop();
	//	Video2 = nullptr;
	//}





	//if (nullptr != Video1 && true == Video1->IsFinished())
	//{
	//	//Video1->Stop();
	//	Video1 = nullptr;
	//	Video2->Play();
	//	return;
	//}

	//if (nullptr != Video1)
	//	return;

	//if (nullptr != Video2 && true == Video2->IsFinished())
	//{
	//	Video2->Stop();
	//	Video2 = nullptr;
	//	return;
	//}

	//if(nullptr == Video1)

	
}
