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



void GameEngineActor::ComponentsUpdate(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		//Ȱ��ȭ�� ������Ʈ�鸸 ���� ��Ű��
		if (false == Component->IsUpdate())
			continue;

		Component->Update(_DeltaTime);
	}
}




void GameEngineActor::ComponentsRender(float _DeltaTime)
{
	for (std::shared_ptr<GameEngineComponent>& Component : ComponentsList)
	{
		//Ȱ��ȭ�� ������Ʈ�鸸 ���� ��Ű��
		if (false == Component->IsUpdate())
			continue;

		Component->Render(_DeltaTime);
	}
}


void GameEngineActor::AccLiveTime(float _LiveTime)
{
	//�ڽ��� ���̺�Ÿ���� ������Ű��
	GameEngineUpdateObject::AccLiveTime(_LiveTime);

	//������Ʈ���� ���̺�Ÿ���� ������Ų��
	for (std::shared_ptr<class GameEngineComponent>& Component : ComponentsList)
	{
		Component->AccLiveTime(_LiveTime);
	}
}
