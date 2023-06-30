#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

class SoundMgr
{
	friend class RCG_GameCore;

public:

	static void ChangeBGM(const std::string_view& _BgmName);

	static void PlaySFX(const std::string_view& _BgmName);

	static void BgmStop();

	static void Update_LoopArea();


	inline static void SetBGMLoop(float _Start, float _End)
	{
		BGMLoopStartSec = _Start;
		BGMLoopEndSec = _End;
	}


	SoundMgr(const SoundMgr& _Other) = delete;
	SoundMgr(SoundMgr&& _Other) noexcept = delete;
	SoundMgr& operator=(const SoundMgr& _Other) = delete;
	SoundMgr& operator=(const SoundMgr&& _Other) noexcept = delete;


protected:
	static void Init();


private:
	static GameEngineSoundPlayer BGM;
	static float BGMLoopStartSec;
	static float BGMLoopEndSec;


	SoundMgr();
	virtual ~SoundMgr() = 0;
};

