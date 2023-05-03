#include "PrecompileHeader.h"
#include "GameEngineCoreWindow.h"

GameEngineCoreWindow::GameEngineCoreWindow()
{

}

GameEngineCoreWindow::~GameEngineCoreWindow()
{

}

void GameEngineCoreWindow::OnGUI(std::shared_ptr<GameEngineLevel> _Level, float _DeltaTime)
{
	if (ImGui::Button("Hello GUI"))
	{
		if (nullptr != Callback)
		{
			Callback();
		}
	}
}
