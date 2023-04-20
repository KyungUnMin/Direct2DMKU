#include "PrecompileHeader.h"
#include "KeyMgr.h"

#include <GameEnginePlatform/GameEngineInput.h>

const std::vector<std::string_view> KeyMgr::IndexToString =
{
	"UpArrow",
	"DownArrow",
	"RightArrow",
	"LeftArrow",
	"Space",

	"DebugF1",
	"DebugF2",
	"DebugF3",
	"DebugF4",
	"DebugF6",
	"DebugF7",
	"DebugF8",
	"DebugF9",


};


void KeyMgr::CreateKey()
{
	std::vector<int> KeyInfo(static_cast<size_t>(KeyNames::COUNT), '?');

	KeyInfo[static_cast<size_t>(KeyNames::UpArrow)] = VK_UP;
	KeyInfo[static_cast<size_t>(KeyNames::DownArrow)] = VK_DOWN;
	KeyInfo[static_cast<size_t>(KeyNames::RightArrow)] = VK_RIGHT;
	KeyInfo[static_cast<size_t>(KeyNames::LeftArrow)] = VK_LEFT;
	KeyInfo[static_cast<size_t>(KeyNames::Space)] = VK_SPACE;

	KeyInfo[static_cast<size_t>(KeyNames::DebugF1)] = VK_F1;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF2)] = VK_F2;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF3)] = VK_F3;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF4)] = VK_F4;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF6)] = VK_F6;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF7)] = VK_F7;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF8)] = VK_F8;
	KeyInfo[static_cast<size_t>(KeyNames::DebugF9)] = VK_F9;

	for (int i = 0; i < KeyInfo.size(); ++i)
	{
		int KeyValue = KeyInfo[i];
		if ('?' == KeyValue)
		{
			std::string ErrorKeyName = IndexToString[i].data();
			MsgAssert(ErrorKeyName + "키를 아직 설정해주지 않았습니다");
			return;
		}

		GameEngineInput::CreateKey(IndexToString[i], KeyValue);
	}
}


bool KeyMgr::IsPress(KeyNames _Name)
{
	return GameEngineInput::IsPress(EnumToString(_Name));
}

bool KeyMgr::IsDown(KeyNames _Name)
{
	return GameEngineInput::IsDown(EnumToString(_Name));
}

bool KeyMgr::IsUp(KeyNames _Name)
{
	return GameEngineInput::IsUp(EnumToString(_Name));
}

bool KeyMgr::IsFree(KeyNames _Name)
{
	return GameEngineInput::IsFree(EnumToString(_Name));
}





KeyMgr::KeyMgr()
{

}

KeyMgr::~KeyMgr()
{

}
