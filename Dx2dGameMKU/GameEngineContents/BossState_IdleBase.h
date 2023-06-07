#pragma once
#include "EnemyState_IdleBase.h"

class BossFSMBase;

class BossState_IdleBase : public EnemyState_IdleBase
{
public:
	BossState_IdleBase();
	virtual ~BossState_IdleBase() = 0;

	BossState_IdleBase(const BossState_IdleBase& _Other) = delete;
	BossState_IdleBase(BossState_IdleBase&& _Other) noexcept = delete;
	BossState_IdleBase& operator=(const BossState_IdleBase& _Other) = delete;
	BossState_IdleBase& operator=(const BossState_IdleBase&& _Other) noexcept = delete;

protected:
	void Start() override;

	inline BossFSMBase* GetBossFsm() const
	{
		return BossFsmPtr;
	}

private:
	BossFSMBase* BossFsmPtr = nullptr;

};

