#include "PrecompileHeader.h"
#include "EnemyState_IdleBase.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "EnemyFSMBase.h"
#include "EnemyState_AttackBase.h"

const std::pair<float, float> EnemyState_IdleBase::SettingTime = { 1.f, 3.f };

EnemyState_IdleBase::EnemyState_IdleBase()
{

}

EnemyState_IdleBase::~EnemyState_IdleBase()
{

}



void EnemyState_IdleBase::EnterState()
{
	EnemyStateBase::EnterState();
	WaitTime = GameEngineRandom::MainRandom.RandomFloat(SettingTime.first, SettingTime.second);
}


bool EnemyState_IdleBase::IsWaitFinished()
{
	return (WaitTime < GetLiveTime());
}

bool EnemyState_IdleBase::IsAttackerEmpty()
{
	const FieldEnemyBase* const CurAttacker = EnemyState_AttackBase::IsAttackAnyone();
	return (nullptr != CurAttacker);
}



bool EnemyState_IdleBase::ChangeAttackState()
{
	//플레이어와 Enemy 사이의 벡터
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();

	//플레이어와 가까이 있으면서 다른 Enemy가 공격중이 아니라면 공격상태로 변경
	if (VecToPlayer.Size() < GetSightRadius())
	{
		if (false == EnemyState_IdleBase::IsAttackerEmpty())
		{
			size_t RandomAttack = GetEnemyFsm()->GetRandomAttack();
			GetFSM()->ChangeState(RandomAttack);
		}

		//플레이어와 가까이 있으면 Idle을 유지하거나 Attack 상태로 빠진다
		return true;
	}

	return false;
}