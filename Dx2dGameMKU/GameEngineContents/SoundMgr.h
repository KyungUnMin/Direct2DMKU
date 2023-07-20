#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

class SoundMgr
{
	friend class RCG_GameCore;
	friend class FieldLevelBase;

public:

	static void ChangeBGM(const std::string_view& _BgmName);

	static GameEngineSoundPlayer PlaySFX(const std::string_view& _BgmName, bool _IsLoop = false);

	static void BgmStop();

	static void BgmPauseOn();
	static void BgmPauseOff();



	static const std::string& GetCurBgmName()
	{
		return CurBgmName;
	}

	static UINT GetBgmPos();
	static void SetBgmPos(UINT _Pos);

	static void BgmFadeOut(const float _Duration);
	static void BgmFadeIn(const float _Duration);

	static void PauseAllSfx();
	static void ResumeAllSfx();


	SoundMgr(const SoundMgr& _Other) = delete;
	SoundMgr(SoundMgr&& _Other) noexcept = delete;
	SoundMgr& operator=(const SoundMgr& _Other) = delete;
	SoundMgr& operator=(const SoundMgr&& _Other) noexcept = delete;


protected:
	static void Init();
	static void Update(float _DeltaTime);
	static void LevelChangeEnd();

private:
	static GameEngineSoundPlayer BGM;
	

	static std::string CurBgmName;
	static std::list<GameEngineSoundPlayer> AllSfx;
	static std::list<GameEngineSoundPlayer> LoopSfxes;


	static void Update_RemoveOldSfx();


	SoundMgr();
	virtual ~SoundMgr() = 0;
};
