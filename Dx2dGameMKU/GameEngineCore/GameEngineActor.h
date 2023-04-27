#pragma once
#include "GameEngineUpdateObject.h"

class GameEngineComponent;

class GameEngineActor : public GameEngineUpdateObject
{
	friend class GameEngineLevel;

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _Other) noexcept = delete;

	inline class GameEngineLevel* GetLevel()
	{
		return Level;
	}

	//������Ʈ ����
	template <typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent()
	{
		std::shared_ptr<GameEngineComponent> NewComponent = std::make_shared<ComponentType>();
		ComponentInit(NewComponent);
		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	virtual void Start(){}
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}

	void AccLiveTime(float _LiveTime) override;

private:
	class GameEngineLevel* Level = nullptr;

	std::list<std::shared_ptr<GameEngineComponent>> ComponentsList;

	//������Ʈ �ʱ�ȭ
	void ComponentInit(std::shared_ptr<GameEngineComponent> _Component);

	//������Ʈ���� Update���� ȣ�������, �� �Լ��� Level���� ȣ���
	void ComponentsUpdate(float _DeltaTime);

	//������Ʈ���� Render���� ȣ�������, �� �Լ��� Level���� ȣ���
	void ComponentsRender(float _DeltaTime);
};

