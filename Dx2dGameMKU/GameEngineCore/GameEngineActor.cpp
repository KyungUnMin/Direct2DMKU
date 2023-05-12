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

	_Component->Level = GetLevel();
	//컴포넌트 생성시 Transform의 부모 관계 기강 다짐
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	//이 오브젝트의 자식으로 등록
	PushChild(_Component);
}

