#pragma once
#include <string_view>

//끄고, 켜기, 디버깅의 기능만을 담당

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

	inline virtual void On()
	{
		UpdateValue = true;
	}

	inline virtual void Off()
	{
		UpdateValue = false;
	}

	inline virtual void Death()
	{
		DeathValue = true;
	}

	inline virtual bool IsDeath()
	{
		return DeathValue;
	}

	virtual bool IsUpdate()
	{
		return UpdateValue && (false == DeathValue);
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

