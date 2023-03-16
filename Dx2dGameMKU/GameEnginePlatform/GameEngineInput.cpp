#include "GameEngineInput.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

std::map<std::string, GameEngineInput::GameEngineKey> GameEngineInput::Keys;
bool GameEngineInput::IsAnyKeyValue = false;

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	//키가 눌렸다면
	if (true == KeyCheck())
	{
		//이번에 처음으로 눌린것이라면
		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
			PressTime = _DeltaTime;
		}

		//이전 프레임에도 눌렸었다면
		else if (true == Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
			PressTime += _DeltaTime;
		}
	}

	//키가 눌리지 않았다면
	else
	{
		PressTime = 0.0f;

		//이전 프레임에서 누르고 있었다면
		if (true == Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = false;
		}

		//이전 프레임에서 키에서 손을 뎄다면
		else if (true == Up)
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}



//----------------------------------------------------------------------------------------



bool GameEngineInput::IsDown(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Down;
}


bool GameEngineInput::IsUp(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Up;
}


bool GameEngineInput::IsPress(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Press;
}


bool GameEngineInput::IsFree(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Free;
}


float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].PressTime;
}


bool GameEngineInput::IsKey(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	return Keys.end() != Keys.find(UpperName);
}


void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	if (Keys.end() != Keys.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
	}

	//_Key = toupper(_Key);
	Keys[UpperName].Key = _Key;
}



GameEngineInput::GameEngineInput()
{

}

GameEngineInput::~GameEngineInput()
{

}



void GameEngineInput::Update(float _DeltaTime)
{
	std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
	std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

	for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
	{
		StartKeyIter->second.Update(_DeltaTime);
	}
}

void GameEngineInput::MouseCursorOff()
{
	ShowCursor(FALSE);
}