#include "PrecompileHeader.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

std::atomic_bool GameEngineThread::End = false;

GameEngineThread::GameEngineThread()
{

}

GameEngineThread::GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	Start(_ThreadName, _CallBack);
}

GameEngineThread::~GameEngineThread()
{
	//자식 스레드가 끝날때까지 이 객체는 파괴되지 않는다
	Join();
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	//외부로부터 해야 할 일을 설정
	CallBack = _CallBack;
	//스레드 생성
	Thread = std::thread(ThreadBaseFunction, this, _ThreadName);
}

void GameEngineThread::ThreadBaseFunction(GameEngineThread* _Thread, std::string _Name)
{
	//스레드에 이름을 설정해주고
	std::wstring WName = GameEngineString::AnsiToUniCode(_Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());

	//인자로 받은 GameEngineThread*의 콜백 호출(인자로 받은 GameEngineThread*를 넣어준다)
	_Thread->CallBack(_Thread);
}

void GameEngineThread::Join()
{
	if (nullptr != CallBack)
	{
		//자식 스레드가 끝날때까지 기다린다
		Thread.join();

		//스레드가 끝나면 콜백을 null로 돌린다
		CallBack = nullptr;
	}
}