#pragma once


class GameEngineThread
{
public:
	GameEngineThread();
	~GameEngineThread();

	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(const GameEngineThread&& _Other) noexcept = delete;

protected:

private:

};

