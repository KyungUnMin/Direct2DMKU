#include "PrecompileHeader.h"
#include "EnemyFSMBase.h"


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
