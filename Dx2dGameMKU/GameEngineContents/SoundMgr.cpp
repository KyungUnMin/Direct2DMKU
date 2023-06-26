#include "PrecompileHeader.h"
#include "SoundMgr.h"

#include "RCGDefine.h"

GameEngineSoundPlayer SoundMgr::BGM;

void SoundMgr::Init()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Sound);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".mp3" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineSound::Load(File.GetFullPath());
	}
}

void SoundMgr::ChangeBGM(const std::string_view& _BgmName)
{
	if (true == BGM.IsValid())
	{
		BGM.Stop();
	}

	BGM = GameEngineSound::Play(_BgmName);
	BGM.SetLoop();
}

void SoundMgr::PlaySFX(const std::string_view& _BgmName)
{
	GameEngineSound::Play(_BgmName);
}

void SoundMgr::BgmStop()
{
	BGM.Stop();
}




SoundMgr::SoundMgr()
{

}

SoundMgr::~SoundMgr()
{

}

