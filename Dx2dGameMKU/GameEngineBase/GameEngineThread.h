#pragma once
#include <string>
#include <functional>
#include <atomic>

class GameEngineThread
{
public:
	GameEngineThread();
	GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);
	~GameEngineThread();

	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(const GameEngineThread&& _Other) noexcept = delete;

	//스레드 생성 및 일감 던지기
	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);

	//실제 스레드가 끝날떄까지 기다리는 함수
	void Join();

	//부모 스레드가 자식 스레드들에게 종료됐음을 알리는 함수
	static void ThreadEnd()
	{
		End = true;
	}

	//부모 스레드가 종료됐는지 확인(스레드 일감에서 이 함수를 통해 스레드 종료 시켜주어야 한다)
	static bool IsThreadEnd()
	{
		return End;
	}
	
protected:


private:
	//부모 스레드가 자식 스레드들에게 종료됐음을 알리는 bool
	static std::atomic_bool End;

	//스레드의 이름을 등록하기 위해 ThreadBaseFunction을 통해 스레드 생성한다
	static void ThreadBaseFunction(GameEngineThread* _Thread, std::string _Name);

	std::thread Thread;
	std::function<void(GameEngineThread*)> CallBack;
};

