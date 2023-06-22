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
	//�ڽĽ����鿡�� ������Ǯ�� ��������� �˸���
	IsRun = false;

	//��� �ڽ� ��������� �ı��ɶ�����
	while (RunningThreadCount)
	{
		// �����带 ������ �ı��� ����Ѵ�
		if (
			FALSE ==
			PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::Destroy), 0, nullptr)
			)
		{
			MsgAssert("�����忡�� ��Ʈ���� ����� �����µ� �����߽��ϴ�.");
		}

		//�ѹ��� ����ϸ� ������ ����� ������ �־���
		Sleep(0);
	}

	//��� �ڽ� ��������� �ı��Ǹ�
	//������Ǯ�� �Ҹ�ȴ�
}


void GameEngineThreadJobQueue::Initialize(const std::string& _ThreadName, int _ThreadCount)
{
	ThreadCount = _ThreadCount;

	//������ ������ 0�̸� CPU�� �ھ� ������ �����ؼ� �� ������ �°� �����带 �����
	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);

		// Cpu ����
		ThreadCount = Info.dwNumberOfProcessors;
	}


	//IOCP�ڵ� �����(ThreadCount ��ŭ �����带 ���� ���̴�)
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	if (nullptr == IOCPHandle)
	{
		MsgAssert("IOCP�ڵ� ������ �����߽��ϴ�.");
		return;
	}


	//���� Ǯ�� ����ִ� ������
	RunningThreadCount = ThreadCount;
	AllThread.resize(ThreadCount);

	//ThreadCount������ŭ ThreadPoolFunction���� �ϴ� ������ ����
	for (size_t i = 0; i < ThreadCount; i++)
	{
		AllThread[i] = std::make_shared<GameEngineThread>();

		AllThread[i]->Start(
			_ThreadName + " " + std::to_string(i),	//������ �̸�
			std::bind(							//�����忡 �ñ� �� �Լ������ͷ� ���
				ThreadPoolFunction,		//��� �Լ�
				this,									//��� �Լ� ������
				AllThread[i].get(),			//���� 1
				IOCPHandle));					//���� 2

		//����� function<void>��� �ؼ� void ������ �Լ��� ����� �� �ִ� ���� �ƴϴ�
		//functional�� ���ڴ� ����� �Լ��� ���� �޶�����
	}
}


//�����忡�� ���۵ǰ� �ִ� �Լ�
void GameEngineThreadJobQueue::ThreadPoolFunction(GameEngineThreadJobQueue* _ThreadPool, GameEngineThread* _Thread, HANDLE _IOCPHandle)
{
	//���� ���������� ��Ŷ�� ũ�⸦ ���۹޴°� �Ϲ���������
	//�츮 ���������� �����尡 �ؾ� �� ��(ThreadWorkType)�� ����´�
	DWORD Byte;

	//�̰� �������� ��� ���Ǵ��� ��Ծ��µ�,
	//�� ���������� �� ��(Job*)�� ���۵Ǿ� �´�
	ULONG_PTR PtrKey;

	//�ƽ��Ե� �����Ҷ��� �ǹ̰� �ִ�
	LPOVERLAPPED OverLapped = nullptr;




	//ThreadPool�� ��ȿ���� �ʴٸ� �̹� �۾��� ������ �����带 �����Ų��
	while (true == _ThreadPool->IsRun)
	{
		//�� ������� �� ���� ���۵� �� ���� �����¿� ����
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);

		//������� �Դٸ� �����尡 �����

		//�ؾ��� ���� Ÿ���� Ȯ��
		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		//�ñ� ���� ó��
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
			//Ǯ���� ����ִ� ������ ������ ����
			--RunningThreadCount;
			//������ ����
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

	//�ڰ� �ִ� �������� �ϳ��� ������ Job�� ������
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::UserWork), reinterpret_cast<unsigned __int64>(NewJob), nullptr);
}
