#pragma once
#include "FSMBase.h"
#include "RCGEnums.h"

enum class BossVersusStateType
{
	PortraitMatch,
	Corner,
	Spark,
	CallName,
	Wait,

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

	void Init(class BossVersus* _UI, BossType _Boss);

	inline bool IsNoiseUI() const
	{
		return (Boss == BossType::Noise);
	}

protected:

private:
	BossType Boss;
};

