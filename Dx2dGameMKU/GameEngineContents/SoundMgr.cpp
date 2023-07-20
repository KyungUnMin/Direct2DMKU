#include "PrecompileHeader.h"
#include "SoundMgr.h"

#include "RCGDefine.h"

GameEngineSoundPlayer SoundMgr::BGM;
std::string SoundMgr::CurBgmName = "";

std::list<GameEngineSoundPlayer> SoundMgr::AllSfx;
std::list<GameEngineSoundPlayer> SoundMgr::LoopSfxes;

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
		LoopSfxes.push_back(SoundPlayer);
		return SoundPlayer;
	}

	//ȿ���� �ִ� ������ �Ѿ��� ��� SFX�� ������� ����
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


	{
		std::list<GameEngineSoundPlayer>::iterator StartIter = LoopSfxes.begin();
		std::list<GameEngineSoundPlayer>::iterator EndIter = LoopSfxes.end();

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
				StartIter = LoopSfxes.erase(StartIter);
			}
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


void SoundMgr::PauseAllSfx() 
{
	for (GameEngineSoundPlayer Sfx : AllSfx)
	{
		Sfx.SetPause(true);
	}

	for (GameEngineSoundPlayer Sfx : LoopSfxes)
	{
		Sfx.SetPause(true);
	}
}

void SoundMgr::ResumeAllSfx()
{
	for (GameEngineSoundPlayer Sfx : AllSfx)
	{
		Sfx.SetPause(false);
	}

	for (GameEngineSoundPlayer Sfx : LoopSfxes)
	{
		Sfx.SetPause(false);
	}
}






SoundMgr::SoundMgr()
{

}

SoundMgr::~SoundMgr()
{

}

