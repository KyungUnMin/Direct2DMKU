#pragma once
#include "GameEngineSpriteRenderer.h"

// Ό³Έν :
class GameEngineUIRenderer : public GameEngineSpriteRenderer
{
public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer() override;

	GameEngineUIRenderer(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _Other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _Other) = delete;
	GameEngineUIRenderer& operator=(GameEngineUIRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

