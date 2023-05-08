#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{

}

GameEngineActor::~GameEngineActor()
{

}


void GameEngineActor::ComponentInit(std::shared_ptr<GameEngineComponent> _Component)
{
	_Component->Actor = this;

	//컴포넌트 생성시 Transform의 부모 관계 기강 다짐
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	//생성한 컴포넌트를 자신의 컴포넌트 리스트에 등록
	ComponentsList.push_back(_Component);
}



void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		//활성화된 컴포넌트들만 동작 시키기
		if (false == Component->IsUpdate())
			continue;

		Component->Update(_DeltaTime);
	}
}




void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		//활성화된 컴포넌트들만 동작 시키기
		if (false == Component->IsUpdate())
			continue;

		Component->Render(_DeltaTime);
	}
}


void GameEngineActor::AccLiveTime(float _LiveTime)
{
	//자신의 라이브타임을 증가시키고
	GameEngineUpdateObject::AccLiveTime(_LiveTime);

	//컴포넌트들의 라이브타임을 증가시킨다
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->AccLiveTime(_LiveTime);
	}
}


void GameEngineActor::ComponentRelease()
{
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComStartIter = ComponentsList.begin();
	std::list<std::shared_ptr<class GameEngineComponent>>::iterator ComEndIter = ComponentsList.end();

	for (; (ComStartIter != ComEndIter); )
	{
		std::shared_ptr<GameEngineComponent> ComPtr = *ComStartIter;

		if (false == ComPtr->IsDeath())
		{
			++ComStartIter;
			continue;
		}

		ComStartIter = ComponentsList.erase(ComStartIter);
	}
}
