#include "PrecompileHeader.h"
#include "SoundMgr.h"

#include "RCGDefine.h"

GameEngineSoundPlayer SoundMgr::BGM;
float SoundMgr::BGMLoopStartSec = 0.f;
float SoundMgr::BGMLoopEndSec = 0.f;
std::string SoundMgr::CurBgmName = "";


void SoundMgr::Init()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Sound);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".mp3", ".wav"});
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

	CurBgmName = _BgmName;
	BGM = GameEngineSound::Play(_BgmName);
	BGM.SetLoop();

	BGMLoopStartSec = 0.f;
	BGMLoopEndSec = 0.f;
}

GameEngineSoundPlayer SoundMgr::PlaySFX(const std::string_view& _BgmName)
{
	return GameEngineSound::Play(_BgmName);
}

void SoundMgr::BgmStop()
{
	BGM.Stop();
}

void SoundMgr::BgmFadeOut(const float _Duration)
{
	BGM.SoundFadeOut(_Duration);
}


void SoundMgr::Update_LoopArea()
{
	//영역 루프를 설정하지 않은 경우
	if ((0.f == BGMLoopStartSec) && (0.f == BGMLoopEndSec))
		return;

	if (BGM.getPosition() < BGMLoopEndSec)
		return;

	BGM.SetPosition(BGMLoopStartSec);
}






SoundMgr::SoundMgr()
{

}

SoundMgr::~SoundMgr()
{

}

