#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

class SoundMgr
{
	friend class RCG_GameCore;

public:

	static void ChangeBGM(const std::string_view& _BgmName);

	static GameEngineSoundPlayer PlaySFX(const std::string_view& _BgmName);

	static void BgmStop();

	static void Update_LoopArea();


	inline static void SetBGMLoop(float _Start, float _End)
	{
		BGMLoopStartSec = _Start;
		BGMLoopEndSec = _End;
	}

	static const std::string& GetCurBgmName()
	{
		return CurBgmName;
	}

	static void BgmFadeOut(const float _Duration);


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

	static std::string CurBgmName;

	SoundMgr();
	virtual ~SoundMgr() = 0;
};
