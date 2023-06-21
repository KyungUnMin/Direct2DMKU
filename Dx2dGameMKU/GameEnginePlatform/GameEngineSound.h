#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>
#include <unordered_map>

class GameEngineSoundPlayer
{
private:
	FMOD::Channel* Channel = nullptr;

public:
	GameEngineSoundPlayer()
	{

	}

	GameEngineSoundPlayer(FMOD::Channel* _Channel)
		: Channel(_Channel)
	{

	}

	void Stop()
	{
		Channel->stop();
	}

	//재생속도 배율
	void SetPitch(float _Pitch)
	{
		Channel->setPitch(_Pitch);
	}


	void SetVolume(float _Volume)
	{
		Channel->setVolume(_Volume);
	}

	// -1은 무한루프, 0은 루프X
	void SetLoop(int _Count = -1)
	{
		Channel->setLoopCount(_Count);
	}

	void SetMute(bool _Value)
	{
		Channel->setMute(_Value);
	}

	void SetPause(bool _Value)
	{
		Channel->setPaused(_Value);
	}

	//float으로 _StartSecond를 넣어주면 ms로 보정해서 해당 지점부터 시작
	void SetPosition(float _StartSecond, FMOD_TIMEUNIT _TimeUnit = FMOD_TIMEUNIT_MS)
	{
		Channel->setPosition(static_cast<UINT>(_StartSecond * 1000.f), _TimeUnit);
	}

	//_StartSecond ~_EndSecond 까지 반복
	void SetLoopPoint(float _StartSecond, float _EndSecond, FMOD_TIMEUNIT _TimeUnit = FMOD_TIMEUNIT_MS)
	{
		Channel->setLoopPoints(static_cast<UINT>(_StartSecond * 1000.f), _TimeUnit, static_cast<UINT>(_EndSecond * 1000.f), _TimeUnit);
	}
};

class GameEngineSound
{
private:
	static std::unordered_map<std::string, std::shared_ptr<GameEngineSound>> AllSound;

public:
	static void ResourcesClear();

	static void SoundUpdate();

	GameEngineSound();
	~GameEngineSound();

	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(const GameEngineSound&& _Other) noexcept = delete;

	static void Load(const std::string_view& _Path);

	static void Load(const std::string_view& _Name, const std::string_view& _Path);

	static GameEngineSoundPlayer Play(const std::string_view& _Name);

protected:

private:
	void SoundLoad(const std::string_view& _Path);
	FMOD::Channel* SoundPlay();

	FMOD::Sound* FMODSound = nullptr;
};

