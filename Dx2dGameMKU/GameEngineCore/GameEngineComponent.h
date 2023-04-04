#pragma once
#include "GameEngineActor.h"

class GameEngineActor;

class GameEngineComponent : public GameEngineUpdateObject
{
	friend GameEngineActor;

public:
	GameEngineComponent();
	~GameEngineComponent();

	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(const GameEngineComponent&& _Other) noexcept = delete;

	inline GameEngineActor* GetActor() const 
	{
		return Actor;
	}

	inline GameEngineLevel* GetLevel() const
	{
		return Actor->GetLevel();
	}

protected:

private:
	GameEngineActor* Actor = nullptr;

	void SetActor(GameEngineActor* _Actor);
};

