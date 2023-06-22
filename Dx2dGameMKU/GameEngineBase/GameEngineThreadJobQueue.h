#pragma once
#include <functional>
#include <Windows.h>


//�����尡 ó���ؾ� �� ���� Ÿ��
enum ThreadWorkType
{
	UserWork = -1,
	Destroy = -2
};

class GameEngineThread;

//������ Ǯ
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

	//�� �Լ��� ���� ������ Ǯ�� ���� �ñ��
	void Work(std::function<void(GameEngineThread*)> _Work);

	//������ Ǯ�� _ThreadCount������ŭ ������ ����
	void Initialize(const std::string& _ThreadName, int _ThreadCount = 0);

protected:

private:
	//���� Ǯ�� ����ִ� ������
	static std::atomic_int RunningThreadCount;

	//�����忡�� ���۵ǰ� �ִ� �Լ�
	static void ThreadPoolFunction(
		GameEngineThreadJobQueue* _ThreadPool,
		GameEngineThread* _Thread,
		HANDLE _IOCPHandle);


	HANDLE IOCPHandle = nullptr;
	//Init�Ҷ� ������ ������ ����(�ʱ� ������ ���� ����)
	int ThreadCount = 0;


	//�� ������ Ǯ�� �ı��ƴ��� �ڽ� ������鿡�� �˸��� ���� bool
	std::atomic_bool IsRun = true;

	std::vector<std::shared_ptr<GameEngineThread>> AllThread;
};

