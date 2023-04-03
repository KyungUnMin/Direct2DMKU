#pragma once
#include "GameEngineUpdateObject.h"

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

protected:

private:
	GameEngineActor* Actor = nullptr;

	void SetActor(GameEngineActor* _Actor);
};

