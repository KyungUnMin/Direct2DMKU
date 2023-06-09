#pragma once
#include "GameEngineActor.h"

class GameEngineActor;
class GameEngineLevel;

class GameEngineComponent : public GameEngineObject
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


protected:

private:
	GameEngineActor* Actor = nullptr;

	void SetActor(GameEngineActor* _Actor);
};

