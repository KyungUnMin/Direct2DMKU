#pragma once
#include "StateBase.h"

class BossVersusState_Versus : public StateBase
{
public:
	BossVersusState_Versus();
	~BossVersusState_Versus() override;

	BossVersusState_Versus(const BossVersusState_Versus& _Other) = delete;
	BossVersusState_Versus(BossVersusState_Versus&& _Other) noexcept = delete;
	BossVersusState_Versus& operator=(const BossVersusState_Versus& _Other) = delete;
	BossVersusState_Versus& operator=(const BossVersusState_Versus&& _Other) noexcept = delete;

protected:

private:

};

