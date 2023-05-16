#pragma once
#include "FSMBase.h"

enum class BossVersusStateType
{
	PortraitMatch,
	Corner,
	Fire,
	CallName,
	Versus,

	COUNT
};

class BossVersusUIFSM : public FSMBase
{
public:
	BossVersusUIFSM();
	~BossVersusUIFSM() override;

	BossVersusUIFSM(const BossVersusUIFSM& _Other) = delete;
	BossVersusUIFSM(BossVersusUIFSM&& _Other) noexcept = delete;
	BossVersusUIFSM& operator=(const BossVersusUIFSM& _Other) = delete;
	BossVersusUIFSM& operator=(const BossVersusUIFSM&& _Other) noexcept = delete;

	void Init(class BossVersus* _UI);

protected:

private:

};

