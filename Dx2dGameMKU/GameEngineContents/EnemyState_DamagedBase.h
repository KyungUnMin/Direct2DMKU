#pragma once
#include "EnemyStateBase.h"

class EnemyState_DamagedBase : public EnemyStateBase
{
public:
	EnemyState_DamagedBase();
	~EnemyState_DamagedBase() override;

	EnemyState_DamagedBase(const EnemyState_DamagedBase& _Other) = delete;
	EnemyState_DamagedBase(EnemyState_DamagedBase&& _Other) noexcept = delete;
	EnemyState_DamagedBase& operator=(const EnemyState_DamagedBase& _Other) = delete;
	EnemyState_DamagedBase& operator=(const EnemyState_DamagedBase&& _Other) noexcept = delete;

protected:

private:

};

