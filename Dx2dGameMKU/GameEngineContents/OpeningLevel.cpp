#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>


#include "RCGEnums.h"
#include "RCGDefine.h"

#include "OpeningActor.h"

OpeningLevel::OpeningLevel()
{

}

OpeningLevel::~OpeningLevel()
{

}


void OpeningLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	//엑터들 리소스 로드
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Opening");

	std::vector<GameEngineFile> Images = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& Path : Images)
	{
		GameEngineTexture::Load(Path.GetFullPath());
	}

	OpeningCtrl = CreateActor<OpeningActor>();

	//비디오 로드 및 재생
	RCGDefine::MoveContentPath(Dir, ResType::Video);
	OpeningVideo = GameEngineVideo::Load(Dir.GetPlusFileName("Opening.avi").GetFullPath());
}


void OpeningLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (nullptr == OpeningVideo)
		return;

	if (GameEngineVideo::VideoState::Running == GameEngineVideo::GetCurState())
		return;

	//비디오가 끝났을때
	OpeningCtrl->VideoOff();
	OpeningVideo = nullptr;
}

void OpeningLevel::LevelChangeStart()
{
	OpeningVideo->Play();
}



void OpeningLevel::LevelChangeEnd()
{
	OpeningCtrl->Death();

}
