#pragma once
#include "GameEngineObject.h"

class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _Other) noexcept = delete;

	inline class GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:
	virtual void Start(){}
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}

private:
	class GameEngineLevel* Level = nullptr;
};

