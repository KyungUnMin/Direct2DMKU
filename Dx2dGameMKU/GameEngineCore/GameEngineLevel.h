#pragma once
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	GameEngineTimeEvent TimeEvent;

	GameEngineLevel();
	virtual ~GameEngineLevel();

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(const std::string_view& _Name)
	{
		return CreateActor<ActorType>(0, _Name);
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();

		//이름이 존재하지 않으면 클래스 명으로 이름 설정
		std::string Name = _Name.data();
		if ("" == Name)
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		//Order 및 Parent 설정
		ActorInit(NewActor, _Order, this);
		Actors[_Order].push_back(NewActor);
		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return MainCamera;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime);

private:
	std::shared_ptr<GameEngineCamera> MainCamera;
	std::shared_ptr<GameEngineCamera> UICamera;

	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;

	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);
};

