#pragma once
#include "GameEngineObject.h"

class GameEngineUpdateObject : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	GameEngineUpdateObject();
	~GameEngineUpdateObject() override;

	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject&& _Other) noexcept = delete;

};

