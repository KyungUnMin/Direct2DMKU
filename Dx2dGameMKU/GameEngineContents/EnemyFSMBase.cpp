#include "PrecompileHeader.h"
#include "EnemyFSMBase.h"

#include "EnemyStateBase.h"

EnemyFSMBase::EnemyFSMBase()
{

}

EnemyFSMBase::~EnemyFSMBase()
{

}

FieldEnemyBase* EnemyFSMBase::GetEnemy() const
{
	if(nullptr == Enemy)
	{
		MsgAssert("자식쪽에서 EnemyFSMBase의 Init함수를 호출해주지 않았습니다");
		return nullptr;
	}

	return Enemy;
}

bool EnemyFSMBase::IsUnbeatableState()
{
	std::shared_ptr<StateBase> StatePtr = GetNowStatePtr();

	std::shared_ptr<EnemyStateBase> EnemyState = std::dynamic_pointer_cast<EnemyStateBase>(StatePtr);
	if (nullptr == EnemyState)
	{
		MsgAssert("Enemy State중에 EnemyStateBase를 상속받지 않은 State가 존재합니다");
		return false;
	}

	return EnemyState->IsUnbeatable();
}
