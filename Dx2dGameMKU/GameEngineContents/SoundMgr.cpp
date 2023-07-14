#include "PrecompileHeader.h"
#include "SoundMgr.h"

#include "RCGDefine.h"

GameEngineSoundPlayer SoundMgr::BGM;
std::string SoundMgr::CurBgmName = "";

std::list<GameEngineSoundPlayer> SoundMgr::AllSfx;

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
}

GameEngineSoundPlayer SoundMgr::PlaySFX(const std::string_view& _BgmName, bool _IsLoop /*= false*/)
{
	if (true == _IsLoop)
	{
		GameEngineSoundPlayer SoundPlayer = GameEngineSound::Play(_BgmName);
		SoundPlayer.SetLoop(-1);
		return SoundPlayer;
	}

	//효과음 최대 갯수를 넘었을 경우 SFX를 출력하지 않음
	if (10 < AllSfx.size())
	{
		GameEngineSoundPlayer OldSoundPlayer = AllSfx.back();
		AllSfx.pop_back();

		bool IsPlay = false;
		OldSoundPlayer.isPlaying(&IsPlay);
		if (true == IsPlay)
		{
			OldSoundPlayer.Stop();
		}
	}

	GameEngineSoundPlayer SoundPlayer = GameEngineSound::Play(_BgmName);
	AllSfx.push_back(SoundPlayer);
	return SoundPlayer;
}

void SoundMgr::BgmStop()
{
	BGM.Stop();
}

void SoundMgr::BgmPauseOn()
{
	BGM.SetPause(true);
}

void SoundMgr::BgmPauseOff() 
{
	BGM.SetPause(false);
}

UINT SoundMgr::GetBgmPos()
{
	if (false == BGM.IsValid())
		return 0;

	return BGM.getPosition();
}

void SoundMgr::SetBgmPos(UINT _Pos)
{
	BGM.setPosition(_Pos);
}


void SoundMgr::BgmFadeOut(const float _Duration)
{
	BGM.SoundFadeOut(_Duration);
}

void SoundMgr::BgmFadeIn(const float _Duration)
{
	BGM.SoundFadeIn(_Duration);
}



void SoundMgr::Update(float _DeltaTime)
{
	Update_RemoveOldSfx();
}




void SoundMgr::Update_RemoveOldSfx()
{
	std::list<GameEngineSoundPlayer>::iterator StartIter = AllSfx.begin();
	std::list<GameEngineSoundPlayer>::iterator EndIter = AllSfx.end();

	while (StartIter != EndIter)
	{
		bool IsPlay = false;
		StartIter->isPlaying(&IsPlay);
		if (true == IsPlay)
		{
			++StartIter;
		}
		else
		{
			StartIter = AllSfx.erase(StartIter);
		}
	}
}


void SoundMgr::LevelChangeEnd()
{
	while (false == AllSfx.empty())
	{
		GameEngineSoundPlayer& SoundPlayer = AllSfx.front();
		
		bool IsPlay = false;
		SoundPlayer.isPlaying(&IsPlay);
		if (true == IsPlay)
		{
			SoundPlayer.Stop();
		}

		AllSfx.pop_front();
	}

	AllSfx.clear();
}




SoundMgr::SoundMgr()
{

}

SoundMgr::~SoundMgr()
{

}

