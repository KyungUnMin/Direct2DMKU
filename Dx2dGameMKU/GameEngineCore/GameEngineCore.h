#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <typeinfo>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineLevel.h"

class GameEngineCore
{
	friend class GameEngineTexture;
	friend class GameEngineSprite;

public:
	GameEngineCore();
	~GameEngineCore();

	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(const GameEngineCore&& _Other) noexcept = delete;

	static void Start(HINSTANCE _Instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos = { 0, 0 }, float4 _Size = { 1280, 720 });

	template<typename LevelType>
	static std::shared_ptr<LevelType> CreateLevel(const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();
		std::string Name = _Name.data();

		//이름이 없을땐 클래스 명으로 이름 만들기
		if ("" == _Name)
		{
			//이름 추출
			const type_info& Info = typeid(LevelType);
			Name = Info.name();

			//"class 클래스명"의 앞부분 "class "지우기
			Name.replace(0, 6, "");
		}

		Name = GameEngineString::ToUpper(Name);

		if (LevelMap.end() != LevelMap.find(Name))
		{
			MsgAssert("같은 이름의 레벨을 2개 만들순 없습니다");
		}

		//레벨의 Loading함수 호출
		LevelInit(NewLevel);

		LevelMap.insert(std::make_pair(Name, NewLevel));
		return std::dynamic_pointer_cast<LevelType>(NewLevel);
	}

	static void ChangeLevel(const std::string_view& _Name);

	static std::shared_ptr<GameEngineLevel> GetCurLevel()
	{
		return MainLevel;
	}

protected:

private:
	//레벨이 Start되는 순간만 포인터에 값이 존재한다
	static class GameEngineLevel* CurLoadLevel;

	static void CoreResourceInit();
	static void CoreResourceEnd();

	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level);

	static void EngineStart(std::function<void()> _ContentsStart);
	static void EngineUpdate();
	static void EngineEnd(std::function<void()> _ContentsEnd);

	static std::map<std::string, std::shared_ptr<GameEngineLevel>> LevelMap;
	static std::shared_ptr<GameEngineLevel> MainLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
};

