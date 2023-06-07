#include "PrecompileHeader.h"
#include "BossState_IdleBase.h"

#include "BossFSMBase.h"

BossState_IdleBase::BossState_IdleBase()
{

}

BossState_IdleBase::~BossState_IdleBase()
{

}

void BossState_IdleBase::Start()
{
	EnemyState_IdleBase::Start();

	BossFsmPtr = GetConvertFSM<BossFSMBase>();
	if (nullptr != BossFsmPtr)
		return;
	
	MsgAssert("BossFSMBase�� �ƴ� FSM�� BossState_IdleBase�� ��ӹ��� State�� ������ �ֽ��ϴ�");
}
