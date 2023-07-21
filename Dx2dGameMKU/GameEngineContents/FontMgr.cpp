#include "PrecompileHeader.h"
#include "FontMgr.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineFont.h>

std::vector<GameEngineFile> FontMgr::FontFiles;
std::vector<std::string_view> FontMgr::FontNames =
{
	"빙그레체",
	"나눔스퀘어_ac",
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
			MsgAssert("폰트 로드에 실패했습니다.");
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
			MsgAssert("폰트 삭제에 실패했습니다.");
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
