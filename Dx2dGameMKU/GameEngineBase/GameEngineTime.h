#pragma once
#include <Windows.h>

class GameEngineTime
{
public:
	static GameEngineTime GlobalTime;

	GameEngineTime();
	~GameEngineTime();

	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset();

	float TimeCheck();

	inline float GetDeltaTime() const
	{
		return floatDeltaTime;
	}

	inline float GetTimeScaleDeltaTime() const
	{
		return floatDeltaTime * TimeScale;
	}

	inline void SetTimeScale(float _TimeScale)
	{
		TimeScale = _TimeScale;
	}

protected:


private:
	__int64				Tick							= 0;
	LARGE_INTEGER Prev							= LARGE_INTEGER();
	LARGE_INTEGER Current					= LARGE_INTEGER();
	LARGE_INTEGER Second						= LARGE_INTEGER();
	double					DoubleDeltaTime		= 0.0;
	float					floatDeltaTime		= 0.0f;
	float					TimeScale				= 1.f;
};

