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
		MsgAssert("�̹� �ʱ�ȭ�� �ִ�ü���� �� �ʱ�ȭ �� �� �����ϴ�");
		return;
	}

	MaxHp = static_cast<size_t>(_MaxHp);
	PhaseDivicer = (MaxHp / PhaseCount) + 1;
}



void BossFSMBase::CalPhase(int _CurHp)
{
	if (0 == PhaseDivicer)
	{
		MsgAssert("���� ������ �ִ� ü���� ���������� �ʾƼ� �������� Phase�� ����� �� �����ϴ�");
		return;
	}

	//ü�¿� ���� Phase ���
	for (size_t i = 1; i <= PhaseCount; ++i)
	{
		if (_CurHp <= static_cast<int>(PhaseDivicer * i))
		{
			CurPhase = static_cast<size_t>(PhaseCount - i);
			return;
		}
	}

	MsgAssert("Phase�� ����ϴ� ������ �߸� �Ǿ����ϴ�");
}
