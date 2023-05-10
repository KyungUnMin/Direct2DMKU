#include "PrecompileHeader.h"
#include "EnemyState_Walk.h"

EnemyState_Walk::EnemyState_Walk()
{

}

EnemyState_Walk::~EnemyState_Walk()
{

}


void EnemyState_Walk::EnterState() 
{
	EnemyStateBase::EnterState();


}

void EnemyState_Walk::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (nullptr != EnemyStateBase::CheckCallback && true == EnemyStateBase::CheckCallback())
		return;

	int a = 0;
}