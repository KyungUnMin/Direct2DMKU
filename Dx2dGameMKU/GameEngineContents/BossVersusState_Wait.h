#pragma once
#include "StateBase.h"

class BossVersusState_Wait : public StateBase
{
public:
	BossVersusState_Wait();
	~BossVersusState_Wait() override;

	BossVersusState_Wait(const BossVersusState_Wait& _Other) = delete;
	BossVersusState_Wait(BossVersusState_Wait&& _Other) noexcept = delete;
	BossVersusState_Wait& operator=(const BossVersusState_Wait& _Other) = delete;
	BossVersusState_Wait& operator=(const BossVersusState_Wait&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	float Duration = 3.f;
};

