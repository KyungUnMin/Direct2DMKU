#pragma once


class GameEngineResource
{
public:
	GameEngineResource();
	~GameEngineResource();

	GameEngineResource(const GameEngineResource& _Other) = delete;
	GameEngineResource(GameEngineResource&& _Other) noexcept = delete;
	GameEngineResource& operator=(const GameEngineResource& _Other) = delete;
	GameEngineResource& operator=(const GameEngineResource&& _Other) noexcept = delete;

protected:

private:

};

