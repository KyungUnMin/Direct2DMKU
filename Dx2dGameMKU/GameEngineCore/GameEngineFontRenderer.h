#pragma once
#include "GameEngineRenderer.h"

class GameEngineFont;

class GameEngineFontRenderer : public GameEngineRenderer
{
public:
	GameEngineFontRenderer();
	~GameEngineFontRenderer();

	GameEngineFontRenderer(const GameEngineFontRenderer& _Other) = delete;
	GameEngineFontRenderer(GameEngineFontRenderer&& _Other) noexcept = delete;
	GameEngineFontRenderer& operator=(const GameEngineFontRenderer& _Other) = delete;
	GameEngineFontRenderer& operator=(const GameEngineFontRenderer&& _Other) noexcept = delete;

	void SetFont(const std::string_view& _Font);
	void SetText(const std::string_view& _Text);

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	std::string Text = "";
	std::shared_ptr<GameEngineFont> Font = nullptr;
};

