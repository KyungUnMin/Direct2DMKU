#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>


#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"

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

	//���͵� ���ҽ� �ε�
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

	//���� �ε� �� ���
	RCGDefine::MoveContentPath(Dir, ResType::Video);
	OpeningVideo = GameEngineVideo::Load(Dir.GetPlusFileName("Opening.avi").GetFullPath());
	OpeningVideo->Play();
}


void OpeningLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (nullptr == OpeningVideo)
		return;

	//������ ��������
	if (true == OpeningVideo->IsFinished())
	{
		OpeningCtrl->VideoOff();
		OpeningVideo->Stop();
		OpeningVideo = nullptr;
	}

	//������ ��ŵ������
	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		OpeningCtrl->VideoOff();
		OpeningVideo->Stop();
		OpeningVideo = nullptr;
	}
}



void OpeningLevel::LevelChangeEnd()
{
	OpeningCtrl->Death();

}
