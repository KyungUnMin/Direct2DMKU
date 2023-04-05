#pragma once
#include <string_view>

//����, �ѱ�, ������� ��ɸ��� ���

class GameEngineObjectBase
{
public:
	GameEngineObjectBase();
	virtual ~GameEngineObjectBase();

	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _Other) noexcept = delete;

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
		ActiveValue = true;
	}

	inline void Off()
	{
		ActiveValue = false;
	}

	inline void Death()
	{
		DeathValue = true;
	}

	void DebugOn()
	{
		DebugValue = true;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool ActiveValue = true;
	bool DeathValue = false;
	bool DebugValue = false;
	int Order = 0;
};

