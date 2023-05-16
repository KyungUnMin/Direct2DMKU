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

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	inline void On()
	{
		UpdateValue = true;
	}

	inline void Off()
	{
		UpdateValue = false;
	}

	inline void Death()
	{
		DeathValue = true;
	}

	virtual bool IsDeath()
	{
		return DeathValue;
	}

	virtual bool IsUpdate()
	{
		return UpdateValue;
	}

	void DebugOn()
	{
		DebugValue = true;
	}

	void DebugOff()
	{
		DebugValue = false;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool UpdateValue = true;
	bool DeathValue = false;
	bool DebugValue = false;
	int Order = 0;
};

