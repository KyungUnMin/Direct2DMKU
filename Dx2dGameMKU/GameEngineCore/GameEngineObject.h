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


	////////////////////////////////Transform
private:
	GameEngineTransform Transform;
};

