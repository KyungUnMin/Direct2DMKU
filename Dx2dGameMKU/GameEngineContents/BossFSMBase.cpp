#include "PrecompileHeader.h"
#include "BossFSMBase.h"

const size_t BossFSMBase::PhaseCount = 3;


BossFSMBase::BossFSMBase()
{

}

BossFSMBase::~BossFSMBase()
{

}


void BossFSMBase::SetMaxHp(int _MaxHp)
{
	if (0 != MaxHp)
	{
		MsgAssert("이미 초기화한 최대체력을 또 초기화 할 순 없습니다");
		return;
	}

	MaxHp = static_cast<size_t>(_MaxHp);
	PhaseDivicer = (MaxHp / PhaseCount) + 1;
}



void BossFSMBase::CalPhase(int _CurHp)
{
	if (0 == PhaseDivicer)
	{
		MsgAssert("보스 몬스터의 최대 체력을 설정해주지 않아서 보스전의 Phase를 계산할 수 없습니다");
		return;
	}

	//체력에 따른 Phase 계산
	for (size_t i = 1; i <= PhaseCount; ++i)
	{
		if (_CurHp <= static_cast<int>(PhaseDivicer * i))
		{
			CurPhase = static_cast<size_t>(PhaseCount - i);
			return;
		}
	}

	MsgAssert("Phase를 계산하는 수식이 잘못 되었습니다");
}
