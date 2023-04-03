#pragma once
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "GameEngineUpdateObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineLevel : public GameEngineUpdateObject
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

		//�̸��� �������� ������ Ŭ���� ������ �̸� ����
		std::string Name = _Name.data();
		if ("" == Name)
		{
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		//Order �� Parent ����
		ActorInit(NewActor, _Order, this);
		
		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return MainCamera;
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime);

private:
	std::shared_ptr<GameEngineCamera> MainCamera;
	std::shared_ptr<GameEngineCamera> UICamera;

	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;

	//������ ���� �ʱ�ȭ
	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);
};

