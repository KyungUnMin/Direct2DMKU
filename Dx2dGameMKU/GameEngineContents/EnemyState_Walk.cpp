#include "PrecompileHeader.h"
#include "EnemyState_Walk.h"

#include "EnemyFSM.h"
#include "FieldEnemyBase.h"

EnemyState_Walk::EnemyState_Walk()
{

}

EnemyState_Walk::~EnemyState_Walk()
{

}


void EnemyState_Walk::EnterState() 
{
	EnemyStateBase::EnterState();

	FsmPtr = GetConvertFSM<EnemyFSM>();
	EnemyPtr = FsmPtr->GetEnemy();
}

void EnemyState_Walk::Update(float _DeltaTime) 
{
	EnemyStateBase::Update(_DeltaTime);

	if (nullptr != EnemyStateBase::CheckCallback && true == EnemyStateBase::CheckCallback())
		return;

	EnemyPtr->GetTransform()->AddLocalPosition(float4::Right * _DeltaTime * 10.f);
}