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

void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		Component->Update(_DeltaTime);
	}
}

void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		Component->Render(_DeltaTime);
	}
}
