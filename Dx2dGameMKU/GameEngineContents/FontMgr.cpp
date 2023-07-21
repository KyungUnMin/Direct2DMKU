#include "PrecompileHeader.h"
#include "FontMgr.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineFont.h>

std::vector<GameEngineFile> FontMgr::FontFiles;
std::vector<std::string_view> FontMgr::FontNames =
{
	"���׷�ü",
	"����������_ac",
};




void FontMgr::Init()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResource");
	Dir.Move("ContentsResource");
	Dir.Move("Font");
	FontFiles = Dir.GetAllFile({ ".otf", ".ttf" });

	for (const GameEngineFile& File : FontFiles)
	{
		if (0 == AddFontResourceA(File.GetFullPath().c_str()))
		{
			MsgAssert("��Ʈ �ε忡 �����߽��ϴ�.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}

	for (size_t i = 0; i < FontNames.size(); ++i)
	{
		GameEngineFont::Load(FontNames[i]);
	}
}


void FontMgr::Clear()
{
	for (const GameEngineFile& File : FontFiles)
	{
		if (0 == RemoveFontResourceA(File.GetFullPath().data()))
		{
			MsgAssert("��Ʈ ������ �����߽��ϴ�.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

FontMgr::FontMgr()
{

}

FontMgr::~FontMgr()
{

}
