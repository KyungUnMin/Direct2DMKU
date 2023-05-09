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

	//������Ʈ ������ Transform�� �θ� ���� �Ⱝ ����
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	//������ ������Ʈ�� �ڽ��� ������Ʈ ����Ʈ�� ���
	ComponentsList.push_back(_Component);
}



void GameEngineActor::Release()
{
	GameEngineObject::Release();

	//TODO
}


