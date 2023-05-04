#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineGUI.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{

}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	//���� ī�޶� ���� ������� ��� ���͵��� ���̺�Ÿ���� �帥��
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			if (false == Actor->IsUpdate())
				continue;


			Actor->AccLiveTime(_DeltaTime);
		}
	}


	//���� ī�޶� ����϶� ī�޶� �����ϰ� ������Ʈ ����X
	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}


	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			//��Ȱ��ȭ�� ���͵��� ���۽�Ű�� ����
			if (false == Actor->IsUpdate())
				continue;

			Actor->Update(_DeltaTime);
			Actor->ComponentsUpdate(_DeltaTime);
		}
	}

}

void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//���� �����Ͷ����� ������ ���� GPU�� �� ��� ���� ���
	GetMainCamera()->Setting();

	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
			Actor->ComponentsRender(_DeltaTime);
		}
	}

	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator Start = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator End = ActorList.end();

		for (; Start != End; )
		{
			std::shared_ptr<GameEngineActor> ReleaseActor = *Start;

			if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
			{
				++Start;
				continue;
			}

			ReleaseActor->Release();
			Start = ActorList.erase(Start);
		}
	}

}


//������ ���� �ʱ�ȭ
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	_Actor->SetOrder(_Order);
	_Actor->Start();

	Actors[_Order].push_back(_Actor);
}

