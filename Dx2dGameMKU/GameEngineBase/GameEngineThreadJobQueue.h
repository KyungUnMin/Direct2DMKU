#pragma once
#include <functional>
#include <Windows.h>


//스레드가 처리해야 할 일의 타입
enum ThreadWorkType
{
	UserWork = -1,
	Destroy = -2
};

class GameEngineThread;

//스레드 풀
class GameEngineThreadJobQueue
{
private:
	class Job
	{
	public:
		std::function<void(GameEngineThread*)> Function;
	};


public:
	GameEngineThreadJobQueue();
	~GameEngineThreadJobQueue();

	GameEngineThreadJobQueue(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue(GameEngineThreadJobQueue&& _Other) noexcept = delete;
	GameEngineThreadJobQueue& operator=(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue& operator=(const GameEngineThreadJobQueue&& _Other) noexcept = delete;

	//이 함수를 통해 스레드 풀에 일을 맡긴다
	void Work(std::function<void(GameEngineThread*)> _Work);

	//스레드 풀에 _ThreadCount갯수만큼 스레드 생성
	void Initialize(const std::string& _ThreadName, int _ThreadCount = 0);

protected:

private:
	//현재 풀에 살아있는 스레드
	static std::atomic_int RunningThreadCount;

	//스레드에서 동작되고 있는 함수
	static void ThreadPoolFunction(
		GameEngineThreadJobQueue* _ThreadPool,
		GameEngineThread* _Thread,
		HANDLE _IOCPHandle);


	HANDLE IOCPHandle = nullptr;
	//Init할때 생성할 스레드 갯수(초기 스레드 생성 갯수)
	int ThreadCount = 0;


	//이 스레드 풀이 파괴됐는지 자식 스레드들에게 알리기 위한 bool
	std::atomic_bool IsRun = true;

	std::vector<std::shared_ptr<GameEngineThread>> AllThread;
};

