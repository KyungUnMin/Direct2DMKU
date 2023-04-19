#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{

}




void GameEngineLevel::Update(float _DeltaTime)
{
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
			Actor->Update(_DeltaTime);
			Actor->ComponentsUpdate(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render(float _DeltaTime)
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
}

//������ ���� �ʱ�ȭ
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	_Actor->SetOrder(_Order);
	_Actor->Start();

	Actors[_Order].push_back(_Actor);
}