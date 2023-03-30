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
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render(float _DeltaTime)
{
	for (std::pair<int, std::list<std::shared_ptr<GameEngineActor>>> OrderGroup : Actors)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = OrderGroup.second;

		for (std::shared_ptr<GameEngineActor> Actor : ActorList)
		{
			Actor->Render(_DeltaTime);
		}
	}
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	_Actor->SetParent(_Level);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}