#pragma once
#include "StateBase.h"

class BossVersusState_Fire : public StateBase
{
public:
	BossVersusState_Fire();
	~BossVersusState_Fire() override;

	BossVersusState_Fire(const BossVersusState_Fire& _Other) = delete;
	BossVersusState_Fire(BossVersusState_Fire&& _Other) noexcept = delete;
	BossVersusState_Fire& operator=(const BossVersusState_Fire& _Other) = delete;
	BossVersusState_Fire& operator=(const BossVersusState_Fire&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

