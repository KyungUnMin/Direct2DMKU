#pragma once
#include "GameEngineGUI.h"
#include "GameEngineLevel.h"

class GameEngineCoreWindow : public GameEngineGUIWindow
{
public:
	GameEngineCoreWindow();
	~GameEngineCoreWindow();

	GameEngineCoreWindow(const GameEngineCoreWindow& _Other) = delete;
	GameEngineCoreWindow(GameEngineCoreWindow&& _Other) noexcept = delete;
	GameEngineCoreWindow& operator=(const GameEngineCoreWindow& _Other) = delete;
	GameEngineCoreWindow& operator=(const GameEngineCoreWindow&& _Other) noexcept = delete;

	std::function<void()> Callback;

	void OnGUI(std::shared_ptr<GameEngineLevel> _Level, float _DeltaTime) override;

protected:

private:

};

