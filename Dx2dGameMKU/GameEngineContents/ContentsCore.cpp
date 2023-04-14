#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include "TestLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

#include <GameEnginePlatform/GameEngineWindow.h>
#include "DirectShow.h"

std::shared_ptr<CDirectShow> ContentsCore::DS;

void ContentsCore::GameStart()
{
	new bool;

	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::ChangeLevel("TestLevel");

	
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResource");
	Dir.Move("ContentsResource");
	std::string Path = Dir.GetPlusFileName("Bossintros_Yamada.avi").GetPathToString();

	DS = std::make_shared<CDirectShow>(STREAM_TYPE_MOVIE);

	DS->PlayClip(GameEngineWindow::GetHWnd(), const_cast<char*>(Path.c_str()));
}

void ContentsCore::GameEnd()
{
}
