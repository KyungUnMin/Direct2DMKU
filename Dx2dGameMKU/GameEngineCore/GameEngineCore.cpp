#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineDevice.h"

std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;
std::shared_ptr<GameEngineLevel> GameEngineCore::MainLevel = nullptr;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel = nullptr;


GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}






void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	//디바이스 초기화
	GameEngineDevice::Initialize();

	//리소스 생성
	CoreResourceInit();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("시작 컨텐츠가 존재하지 않습니다");
	}

	_ContentsStart();
}

void GameEngineCore::EngineUpdate()
{
	if (nullptr != NextLevel)
	{
		MainLevel = NextLevel;
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("아무런 레벨도 동작하지 않고 있습니다");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();
	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	//이벤트 시간 동작
	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);

	//렌더링을 시작하기 전에 이전 이미지들을 지운다
	GameEngineDevice::RenderStart();
	MainLevel->Render(TimeDeltaTime);
	//더블버퍼링을 이용해서 렌더링을 처리한다
	GameEngineDevice::RenderEnd();
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다");
	}

	_ContentsEnd();

	LevelMap.clear();
	CoreResourceEnd();
	GameEngineDevice::Release();
}




void GameEngineCore::Start(HINSTANCE _Instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	GameEngineDebug::LeakCheck();

	if (false == GameEngineInput::IsKey("EnterMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	GameEngineWindow::WindowCreate(_Instance, "MainWindow", _Size, _Pos);
	GameEngineWindow::WindowLoop(std::bind(GameEngineCore::EngineStart, _Start), GameEngineCore::EngineUpdate, std::bind(GameEngineCore::EngineEnd, _End));
}




void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("존재하지 않는 레벨로 체인지 하려고 했습니다");
		return;
	}

	NextLevel = LevelMap[UpperName];
}