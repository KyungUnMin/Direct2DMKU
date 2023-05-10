#include "PrecompileHeader.h"
#include "EnemyState_Idle.h"

EnemyState_Idle::EnemyState_Idle()
{

}

EnemyState_Idle::~EnemyState_Idle()
{

}

void EnemyState_Idle::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (nullptr != EnemyStateBase::CheckCallback && true == EnemyStateBase::CheckCallback())
		return;

	int a = 10;
}
