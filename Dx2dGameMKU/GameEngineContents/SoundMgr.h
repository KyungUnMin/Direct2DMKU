#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

class SoundMgr
{
public:
	static void Init();

	static void ChangeBGM(const std::string_view& _BgmName);

	static void PlaySFX(const std::string_view& _BgmName);

	static void BgmStop();


	SoundMgr(const SoundMgr& _Other) = delete;
	SoundMgr(SoundMgr&& _Other) noexcept = delete;
	SoundMgr& operator=(const SoundMgr& _Other) = delete;
	SoundMgr& operator=(const SoundMgr&& _Other) noexcept = delete;


protected:

private:
	static GameEngineSoundPlayer BGM;

	SoundMgr();
	virtual ~SoundMgr() = 0;
};

