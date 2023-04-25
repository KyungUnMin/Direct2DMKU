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


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	//프리 카메라 모드일땐 카메라 제외하고 업데이트 실행X
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

void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//랜파 래스터라이저 과정을 위해 GPU에 뷰 행렬 정보 등록
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



void GameEngineLevel::Update(float _DeltaTime)
{
	
}

void GameEngineLevel::Render(float _DeltaTime)
{
	
}



//생성한 엑터 초기화
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	_Actor->SetOrder(_Order);
	_Actor->Start();

	Actors[_Order].push_back(_Actor);
}

