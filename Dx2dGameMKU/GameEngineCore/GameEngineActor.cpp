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



void GameEngineActor::Release()
{
	GameEngineObject::Release();

	//TODO
}


