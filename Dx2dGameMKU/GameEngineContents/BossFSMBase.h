#pragma once
#include "EnemyFSMBase.h"

class BossFSMBase : public EnemyFSMBase
{
public:
	BossFSMBase();
	~BossFSMBase();

	BossFSMBase(const BossFSMBase& _Other) = delete;
	BossFSMBase(BossFSMBase&& _Other) noexcept = delete;
	BossFSMBase& operator=(const BossFSMBase& _Other) = delete;
	BossFSMBase& operator=(const BossFSMBase&& _Other) noexcept = delete;

	void SetMaxHp(int _MaxHp);

	void CalPhase(int _CurHp);

	inline bool IsLastPhase() const
	{
		return CurPhase == (PhaseCount - 1);
	}

	inline size_t GetCurPhase() const
	{
		return CurPhase;
	}

protected:


private:
	static const size_t PhaseCount;

	size_t CurPhase = 0;
	size_t PhaseDivicer = 0;
	size_t MaxHp = 0;
};

