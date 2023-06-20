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

