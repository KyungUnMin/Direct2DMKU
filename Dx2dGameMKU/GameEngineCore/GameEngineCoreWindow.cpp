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
	std::string Text = GameEngineString::AnsiToUTF8("한글 테스트");
	if (ImGui::Button(Text.c_str()))
	{
		if (nullptr != Callback)
		{
			Callback();
		}
	}
}
