#pragma once
#include "GameEngineComponent.h"

class GameEngineRenderer : public GameEngineComponent
{
public:
	GameEngineRenderer();
	~GameEngineRenderer() override;

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;
};

