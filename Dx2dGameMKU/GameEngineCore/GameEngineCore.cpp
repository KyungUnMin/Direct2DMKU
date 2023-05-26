#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "GameEngineDevice.h"
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;
std::shared_ptr<GameEngineLevel> GameEngineCore::MainLevel = nullptr;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel = nullptr;

GameEngineLevel* GameEngineCore::CurLoadLevel = nullptr;

GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}






void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	if (false == GameEngineInput::IsKey("GUISwitch"))
	{
		GameEngineInput::CreateKey("GUISwitch", VK_F8);
	}

	//디바이스 초기화
	GameEngineDevice::Initialize();

	//리소스 생성
	CoreResourceInit();

	//내부에서 디바이스와 컨텍스트를 쓰기때문에 디바이스 초기화보다 늦게 이루어져야 한다
	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("시작 컨텐츠가 존재하지 않습니다");
	}

	_ContentsStart();
}

void GameEngineCore::EngineUpdate()
{
	//레벨 전환시 기능
	if (nullptr != NextLevel)
	{
		if (nullptr != MainLevel)
		{
			std::shared_ptr<GameEngineLevel> PrevLevel = MainLevel;

			CurLoadLevel = MainLevel.get();
			MainLevel->LevelChangeEnd();
			CurLoadLevel = nullptr;
			MainLevel->ActorLevelChangeEnd();
		}

		MainLevel = NextLevel;

		if (nullptr != MainLevel)
		{
			CurLoadLevel = MainLevel.get();
			MainLevel->LevelChangeStart();
			CurLoadLevel = nullptr;
			MainLevel->ActorLevelChangeStart();
		}

		//TODO

		NextLevel = nullptr;
		GameEngineTime::GlobalTime.Reset();
	}



	if (nullptr == MainLevel)
	{
		MsgAssert("아무런 레벨도 동작하지 않고 있습니다");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();


	//TimeDeltaTime이 너무 커질때를 방지
	if ((1 / 30.f) < TimeDeltaTime)
	{
		TimeDeltaTime = (1 / 30.f);
	}


	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	//이벤트 시간 동작
	CurLoadLevel = MainLevel.get();
	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->AccLiveTime(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->ActorUpdate(TimeDeltaTime);
	CurLoadLevel = nullptr;


	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	if (State != GameEngineVideo::VideoState::Running)
	{
		//렌더링을 시작하기 전에 이전 이미지들을 지운다
		GameEngineDevice::RenderStart();
		MainLevel->Render(TimeDeltaTime);
		MainLevel->ActorRender(TimeDeltaTime);
		//더블버퍼링을 이용해서 렌더링을 처리한다
		GameEngineDevice::RenderEnd();
	}

	MainLevel->ActorRelease();
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다");
	}

	_ContentsEnd();

	GameEngineGUI::Release();

	LevelMap.clear();
	CoreResourceEnd();
	GameEngineDevice::Release();
	GameEngineWindow::Release();
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


void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	CurLoadLevel = _Level.get();
	_Level->Start();
	CurLoadLevel = nullptr;
}