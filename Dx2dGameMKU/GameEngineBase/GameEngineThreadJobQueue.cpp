#include "PrecompileHeader.h"
#include "GameEngineThreadJobQueue.h"
#include "GameEngineDebug.h"
#include "GameEngineThread.h"

std::atomic_int GameEngineThreadJobQueue::RunningThreadCount = 0;

GameEngineThreadJobQueue::GameEngineThreadJobQueue()
{

}

GameEngineThreadJobQueue::~GameEngineThreadJobQueue()
{
	//자식스레들에게 스레드풀이 종료됐음을 알린다
	IsRun = false;

	//모든 자식 스레드들이 파괴될때까지
	while (RunningThreadCount)
	{
		// 쓰레드를 깨워서 파괴를 명령한다
		if (
			FALSE ==
			PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::Destroy), 0, nullptr)
			)
		{
			MsgAssert("쓰레드에게 디스트로이 명령을 내리는데 실패했습니다.");
		}

		//한번에 명령하면 문제가 생겼던 전적이 있었음
		Sleep(0);
	}

	//모든 자식 스레드들이 파괴되면
	//스레드풀도 소멸된다
}


void GameEngineThreadJobQueue::Initialize(const std::string& _ThreadName, int _ThreadCount)
{
	ThreadCount = _ThreadCount;

	//스레드 갯수가 0이면 CPU의 코어 갯수를 조사해서 그 갯수에 맞게 스레드를 만든다
	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);

		// Cpu 개수
		ThreadCount = Info.dwNumberOfProcessors;
	}


	//IOCP핸들 만들기(ThreadCount 만큼 스레드를 만들 것이다)
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	if (nullptr == IOCPHandle)
	{
		MsgAssert("IOCP핸들 생성에 실패했습니다.");
		return;
	}


	//현재 풀에 살아있는 스레드
	RunningThreadCount = ThreadCount;
	AllThread.resize(ThreadCount);

	//ThreadCount갯수만큼 ThreadPoolFunction일을 하는 스레드 생성
	for (size_t i = 0; i < ThreadCount; i++)
	{
		AllThread[i] = std::make_shared<GameEngineThread>();

		AllThread[i]->Start(
			_ThreadName + " " + std::to_string(i),	//스레드 이름
			std::bind(							//스레드에 맡길 일 함수포인터로 등록
				ThreadPoolFunction,		//멤버 함수
				this,									//멤버 함수 포인터
				AllThread[i].get(),			//인자 1
				IOCPHandle));					//인자 2

		//참고로 function<void>라고 해서 void 인자의 함수만 등록할 수 있는 것이 아니다
		//functional의 인자는 등록한 함수에 따라 달라진다
	}
}


//스레드에서 동작되고 있는 함수
void GameEngineThreadJobQueue::ThreadPoolFunction(GameEngineThreadJobQueue* _ThreadPool, GameEngineThread* _Thread, HANDLE _IOCPHandle)
{
	//실제 서버에서는 패킷의 크기를 전송받는게 일반적이지만
	//우리 엔진에서는 스레드가 해야 할 일(ThreadWorkType)이 날라온다
	DWORD Byte;

	//이건 서버에서 어떻게 사용되는지 까먹었는데,
	//이 엔진에서는 할 일(Job*)이 전송되어 온다
	ULONG_PTR PtrKey;

	//아쉽게도 서버할때만 의미가 있다
	LPOVERLAPPED OverLapped = nullptr;




	//ThreadPool이 유효하지 않다면 이번 작업이 끝나고 스레드를 종료시킨다
	while (true == _ThreadPool->IsRun)
	{
		//이 스레드는 할 일이 전송될 때 까지 대기상태에 들어간다
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);

		//여기까지 왔다면 스레드가 깨어났다

		//해야할 일의 타입을 확인
		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		//맡긴 일을 처리
		case UserWork:
		{
			Job* JobPtr = reinterpret_cast<Job*>(PtrKey);
			if (nullptr != JobPtr->Function)
			{
				JobPtr->Function(_Thread);
			}
			delete JobPtr;
			break;
		}
		case Destroy:
			//풀에서 살아있는 스레드 갯수를 제거
			--RunningThreadCount;
			//스레드 종료
			return;
		default:
			break;
		}
	}
}



void GameEngineThreadJobQueue::Work(std::function<void(GameEngineThread*)> _Work)
{
	Job* NewJob = new Job();
	NewJob->Function = _Work;

	//자고 있는 스레드중 하나를 깨워서 Job을 보낸다
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::UserWork), reinterpret_cast<unsigned __int64>(NewJob), nullptr);
}
