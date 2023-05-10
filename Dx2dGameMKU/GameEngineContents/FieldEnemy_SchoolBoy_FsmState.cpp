#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolBoy.h"

#include "EnemyState_Idle.h"
#include "EnemyState_Walk.h"

void FieldEnemy_SchoolBoy::CreateFsmStates()
{
	FieldEnemyBase::CreateState<EnemyState_Idle>(EnemyStateType::Idle)
		->SetCallBack(std::bind(&FieldEnemy_SchoolBoy::IdleCallBack, this));

	FieldEnemyBase::CreateState<EnemyState_Walk>(EnemyStateType::Walk);

	FieldEnemyBase::ChangeState(EnemyStateType::Idle);
}


bool FieldEnemy_SchoolBoy::IdleCallBack()
{
	FieldEnemyBase::ChangeState(EnemyStateType::Walk);
	return true;
}