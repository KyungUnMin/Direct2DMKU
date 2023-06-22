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

	//������ ���� �� �ϰ� ������
	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);

	//���� �����尡 ���������� ��ٸ��� �Լ�
	void Join();

	//�θ� �����尡 �ڽ� ������鿡�� ��������� �˸��� �Լ�
	static void ThreadEnd()
	{
		End = true;
	}

	//�θ� �����尡 ����ƴ��� Ȯ��(������ �ϰ����� �� �Լ��� ���� ������ ���� �����־�� �Ѵ�)
	static bool IsThreadEnd()
	{
		return End;
	}
	
protected:


private:
	//�θ� �����尡 �ڽ� ������鿡�� ��������� �˸��� bool
	static std::atomic_bool End;

	//�������� �̸��� ����ϱ� ���� ThreadBaseFunction�� ���� ������ �����Ѵ�
	static void ThreadBaseFunction(GameEngineThread* _Thread, std::string _Name);

	std::thread Thread;
	std::function<void(GameEngineThread*)> CallBack;
};

