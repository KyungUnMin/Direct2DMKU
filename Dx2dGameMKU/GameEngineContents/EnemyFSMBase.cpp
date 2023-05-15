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
		MsgAssert("자식쪽에서 EnemyFSMBase의 Init함수를 호출해주지 않았습니다");
		return nullptr;
	}

	return Enemy;
}
