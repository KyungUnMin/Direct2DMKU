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
	
	MsgAssert("BossFSMBase가 아닌 FSM이 BossState_IdleBase를 상속받은 State를 가지고 있습니다");
}
