#pragma once
#include "GameEngineObject.h"

class GameEngineComponent;

class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(const GameEngineActor&& _Other) noexcept = delete;

	
	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> CreateComponent(EnumType _Order)
	{
		return CreateComponent<ActorType>(static_cast<int>(_Order));
	}


	//컴포넌트 생성
	template <typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<GameEngineComponent> NewComponent = std::make_shared<ComponentType>();
		ComponentInit(NewComponent, _Order);
		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

	void SetOrder(int _Order) override;

protected:
	virtual void Start(){}
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}

private:
	//컴포넌트 초기화
	void ComponentInit(std::shared_ptr<GameEngineComponent> _Component, int _Order);
};

