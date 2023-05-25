#pragma once
#include "EnemyStateBase.h"

class EnemyState_IdleBase : public EnemyStateBase
{
public:
	EnemyState_IdleBase();
	~EnemyState_IdleBase() override;

	EnemyState_IdleBase(const EnemyState_IdleBase& _Other) = delete;
	EnemyState_IdleBase(EnemyState_IdleBase&& _Other) noexcept = delete;
	EnemyState_IdleBase& operator=(const EnemyState_IdleBase& _Other) = delete;
	EnemyState_IdleBase& operator=(const EnemyState_IdleBase&& _Other) noexcept = delete;

protected:
	void EnterState() override;

	bool IsWaitFinished();

private:
	static const std::pair<float, float> SettingTime;

	float WaitTime = 0.0f;

};

