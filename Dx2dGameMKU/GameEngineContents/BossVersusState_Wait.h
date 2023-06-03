#pragma once
#include "StateBase.h"

class BossVersus_PostProcessing;

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
	void Start() override;
	void EnterState() override;

private:
	std::shared_ptr<BossVersus_PostProcessing> PostEffect = nullptr;
};

