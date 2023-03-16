#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	//1초 동안 발생한 클럭수
	QueryPerformanceFrequency(&Second);

	//이전 시간(기준시로부터 현재까지 발생한 클럭 수)
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	//시간을 측정하기 시작한 이후로 몇번의 클럭이 발생했는가
	Tick = Current.QuadPart - Prev.QuadPart;

	//(현재시간 - 이전시간) / 1초당 발생하는 클럭수
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	//이전시간 현재시간으로 재갱신
	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);
	return floatDeltaTime;
}
