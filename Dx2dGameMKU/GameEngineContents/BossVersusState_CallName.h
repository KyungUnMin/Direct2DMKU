#pragma once
#include "StateBase.h"

class BossVersusState_CallName : public StateBase
{
public:
	BossVersusState_CallName();
	~BossVersusState_CallName() override;

	BossVersusState_CallName(const BossVersusState_CallName& _Other) = delete;
	BossVersusState_CallName(BossVersusState_CallName&& _Other) noexcept = delete;
	BossVersusState_CallName& operator=(const BossVersusState_CallName& _Other) = delete;
	BossVersusState_CallName& operator=(const BossVersusState_CallName&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DelatTime) override;
	void EnterState() override;

private:



};

