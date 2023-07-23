#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>
#include <unordered_map>

class GameEngineSoundPlayer
{
private:
	FMOD::Channel* Channel = nullptr;

public:
	//특정 컴퓨터에서만 소리가 이상한 문제 해결을 위해 어쩔수 없음
	static bool CanVolumeChange;

	GameEngineSoundPlayer()
	{

	}

	GameEngineSoundPlayer(FMOD::Channel* _Channel)
		: Channel(_Channel)
	{

	}

	inline bool IsValid() const
	{
		return (nullptr != Channel);
	}

	inline void isPlaying(bool* _IsPlaying) const
	{
		if (false == IsValid())
		{
			MsgAssert("유효하지 않은 사운드의 실행 여부를 확인하려 했습니다.");
			return;
		}

		Channel->isPlaying(_IsPlaying);
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
		if (false == CanVolumeChange)
			return;

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


	/// <param name="_Position">사운드 위치 값</param>
	/// <param name="_TimeType">입력 값의 타입을 정합니다</param>
	inline void setPosition(UINT _Position, FMOD_TIMEUNIT _TimeType = FMOD_TIMEUNIT_MS)
	{
		if (false == IsValid())
		{
			MsgAssert("유효하지 않은 사운드의 위치를 설정하려 했습니다");
			return;
		}

		Channel->setPosition(_Position, _TimeType);
	}

	/// <param name="_TimeType">입력 값의 타입을 정합니다</param>
	inline UINT getPosition(FMOD_TIMEUNIT _TimeType = FMOD_TIMEUNIT_MS)
	{
		UINT ResultPosition = 0;

		if (false == IsValid())
		{
			MsgAssert("유효하지 않은 사운드의 위치를 받아오려 했습니다");
			return ResultPosition;
		}

		Channel->getPosition(&ResultPosition, _TimeType);
		return ResultPosition;
	}

	/// <summary>
	/// 사운드를 서서히 키웁니다
	/// </summary>	
	/// <param name="_Volume">재생할 사운드 볼륨을 설정합니다 기본적으로 1.0f 입니다</param>
	void SoundFadeIn(double _Time, float _Volume = 1.0f);

	/// <summary>
	/// 사운드를 서서히 줄입니다
	/// </summary>
	/// <param name="_Volume">정지점의 사운드 볼륨을 설정합니다 기본적으로 0.0f 입니다</param>
	/// <param name="_IsStop">true일 경우 사운드를 Stop 합니다, false 경우 사운드를 일시정지 시킵니다</param>
	void SoundFadeOut(double _Time, float _Volume = 0.0f, bool _IsStop = false);

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

