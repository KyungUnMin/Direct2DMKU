#pragma once
#include "StateBase.h"

class EnemyStateBase : public StateBase
{
public:
	EnemyStateBase();
	virtual ~EnemyStateBase() = 0;

	EnemyStateBase(const EnemyStateBase& _Other) = delete;
	EnemyStateBase(EnemyStateBase&& _Other) noexcept = delete;
	EnemyStateBase& operator=(const EnemyStateBase& _Other) = delete;
	EnemyStateBase& operator=(const EnemyStateBase&& _Other) noexcept = delete;

	inline void SetCallBack(std::function<bool(void)> _CallBack)
	{
		CheckCallback = _CallBack;
	}

protected:
	std::function<bool(void)> CheckCallback = nullptr;

private:
	
	
	
};

