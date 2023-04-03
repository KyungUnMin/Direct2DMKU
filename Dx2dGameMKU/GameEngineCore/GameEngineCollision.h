#pragma once
#include "GameEngineComponent.h"

class GameEngineCollision : public GameEngineComponent
{
public:
	GameEngineCollision();
	~GameEngineCollision() override;

	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _Other) noexcept = delete;

protected:

private:

};

