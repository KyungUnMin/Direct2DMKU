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
		MsgAssert("�ڽ��ʿ��� EnemyFSMBase�� Init�Լ��� ȣ�������� �ʾҽ��ϴ�");
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
		MsgAssert("Enemy State�߿� EnemyStateBase�� ��ӹ��� ���� State�� �����մϴ�");
		return false;
	}

	return EnemyState->IsUnbeatable();
}
