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


GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}






void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	//����̽� �ʱ�ȭ
	GameEngineDevice::Initialize();

	//���ҽ� ����
	CoreResourceInit();

	//���ο��� ����̽��� ���ؽ�Ʈ�� ���⶧���� ����̽� �ʱ�ȭ���� �ʰ� �̷������ �Ѵ�
	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("���� �������� �������� �ʽ��ϴ�");
	}

	_ContentsStart();
}

void GameEngineCore::EngineUpdate()
{
	//���� ��ȯ�� ���
	if (nullptr != NextLevel)
	{
		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeEnd();
		}

		MainLevel = NextLevel;

		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeStart();
		}

		NextLevel = nullptr;
		GameEngineTime::GlobalTime.Reset();
	}



	if (nullptr == MainLevel)
	{
		MsgAssert("�ƹ��� ������ �������� �ʰ� �ֽ��ϴ�");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();


	//TimeDeltaTime�� �ʹ� Ŀ������ ����
	if ((1 / 30.f) < TimeDeltaTime)
	{
		TimeDeltaTime = (1 / 30.f);
	}


	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	//�̺�Ʈ �ð� ����
	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->ActorUpdate(TimeDeltaTime);


	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	if (State != GameEngineVideo::VideoState::Running)
	{
		//�������� �����ϱ� ���� ���� �̹������� �����
		GameEngineDevice::RenderStart();
		MainLevel->Render(TimeDeltaTime);
		MainLevel->ActorRender(TimeDeltaTime);
		//������۸��� �̿��ؼ� �������� ó���Ѵ�
		GameEngineDevice::RenderEnd();
	}

	MainLevel->ActorRelease();
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("�� �������� �������� �ʽ��ϴ�");
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




void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("�������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
		return;
	}

	NextLevel = LevelMap[UpperName];
}