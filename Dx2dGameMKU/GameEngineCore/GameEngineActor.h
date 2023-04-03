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

	//컴포넌트 생성
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

private:
	class GameEngineLevel* Level = nullptr;

	std::list<std::shared_ptr<GameEngineComponent>> ComponentList;

	//컴포넌트 초기화
	void ComponentInit(std::shared_ptr<GameEngineComponent> _Component);
};

