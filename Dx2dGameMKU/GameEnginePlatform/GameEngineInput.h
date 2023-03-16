#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineWindow;

class GameEngineInput
{
	friend GameEngineWindow;

private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool		Down			= false;
		bool		Press			= false;
		bool		Up				= false;
		bool		Free				= true;

		float	PressTime	= 0.0f;
		int		Key				= -1;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(const GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);
	static void CreateKey(const std::string_view& _Name, int _Key);

	static bool IsKey(const std::string_view& _Name);
	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);

	static float GetPressTime(const std::string_view& _Name);

	static void MouseCursorOff();

	static bool IsAnyKey()
	{
		return IsAnyKeyValue;
	}

protected:

private:
	GameEngineInput();
	~GameEngineInput();

	//특정 키에 대한 정보를 빠르게 찾기 위해 map으로 관리
	//맵 내부에서 값형으로 하는 이유 : 어차피 맵 안에서 동적할당함, delete는 맵에 맡기기 위해
	static std::map<std::string, GameEngineKey> Keys;
	static bool IsAnyKeyValue;

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}
};

