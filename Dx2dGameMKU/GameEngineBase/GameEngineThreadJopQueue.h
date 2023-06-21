#pragma once
#include <functional>
#include <Windows.h>

class GameEngineThreadJopQueue
{
public:
	GameEngineThreadJopQueue(int _ThreadCount);
	~GameEngineThreadJopQueue();

	GameEngineThreadJopQueue(const GameEngineThreadJopQueue& _Other) = delete;
	GameEngineThreadJopQueue(GameEngineThreadJopQueue&& _Other) noexcept = delete;
	GameEngineThreadJopQueue& operator=(const GameEngineThreadJopQueue& _Other) = delete;
	GameEngineThreadJopQueue& operator=(const GameEngineThreadJopQueue&& _Other) noexcept = delete;

	void Work(std::function<void()> _Work);

protected:

private:

};

