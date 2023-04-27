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

	void AccLiveTime(float _LiveTime) override;

private:
	class GameEngineLevel* Level = nullptr;

	std::list<std::shared_ptr<GameEngineComponent>> ComponentsList;

	//컴포넌트 초기화
	void ComponentInit(std::shared_ptr<GameEngineComponent> _Component);

	//컴포넌트들의 Update들을 호출시켜줌, 이 함수는 Level에서 호출됨
	void ComponentsUpdate(float _DeltaTime);

	//컴포넌트들의 Render들을 호출시켜줌, 이 함수는 Level에서 호출됨
	void ComponentsRender(float _DeltaTime);
};

