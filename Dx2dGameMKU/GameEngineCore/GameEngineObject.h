#pragma once
#include <list>
#include <string_view>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransform.h"

class GameEngineObject
{
	friend class GameEngineLevel;

public:
	GameEngineObject();
	virtual ~GameEngineObject() = 0;

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;

	inline int GetOrder()
	{
		return Order;
	}

	inline void SetOrder(int _Order)
	{
		Order = _Order;
	}

	inline void On()
	{
		IsActive = true;
	}

	inline void Off()
	{
		IsActive = false;
	}

	inline void Death()
	{
		IsDeath = true;
	}

	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	inline void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	inline GameEngineObject* GetParent()
	{
		return Parent;
	}

	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:


private:
	std::string Name = "";
	bool IsActive = true;
	bool IsDeath = false;
	int Order = 0;

	//순환참조를 사용하지 않기 위해 일반 포인터 이용
	GameEngineObject* Parent = nullptr;
	std::list<std::shared_ptr<GameEngineObject>> Childs;

	////////////////////////////////Transform
private:
	GameEngineTransform Transform;
};

