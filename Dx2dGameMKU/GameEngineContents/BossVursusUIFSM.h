#pragma once
#include "FSMBase.h"

class BossVursus;

class BossVursusUIFSM : public FSMBase
{
public:
	BossVursusUIFSM();
	~BossVursusUIFSM() override;

	BossVursusUIFSM(const BossVursusUIFSM& _Other) = delete;
	BossVursusUIFSM(BossVursusUIFSM&& _Other) noexcept = delete;
	BossVursusUIFSM& operator=(const BossVursusUIFSM& _Other) = delete;
	BossVursusUIFSM& operator=(const BossVursusUIFSM&& _Other) noexcept = delete;

	void Init(BossVursus* _BossUI);

protected:
	

private:
};

