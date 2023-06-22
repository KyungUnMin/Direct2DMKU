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
	//�ڽ� �����尡 ���������� �� ��ü�� �ı����� �ʴ´�
	Join();
}

void GameEngineThread::Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack)
{
	//�ܺηκ��� �ؾ� �� ���� ����
	CallBack = _CallBack;
	//������ ����
	Thread = std::thread(ThreadBaseFunction, this, _ThreadName);
}

void GameEngineThread::ThreadBaseFunction(GameEngineThread* _Thread, std::string _Name)
{
	//�����忡 �̸��� �������ְ�
	std::wstring WName = GameEngineString::AnsiToUniCode(_Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());

	//���ڷ� ���� GameEngineThread*�� �ݹ� ȣ��(���ڷ� ���� GameEngineThread*�� �־��ش�)
	_Thread->CallBack(_Thread);
}

void GameEngineThread::Join()
{
	if (nullptr != CallBack)
	{
		//�ڽ� �����尡 ���������� ��ٸ���
		Thread.join();

		//�����尡 ������ �ݹ��� null�� ������
		CallBack = nullptr;
	}
}