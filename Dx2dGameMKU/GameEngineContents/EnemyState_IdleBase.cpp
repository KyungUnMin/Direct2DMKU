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
	//�÷��̾�� Enemy ������ ����
	float4 VecToPlayer = EnemyStateBase::GetVecToPlayer();

	//�÷��̾�� ������ �����鼭 �ٸ� Enemy�� �������� �ƴ϶�� ���ݻ��·� ����
	if (VecToPlayer.Size() < GetSightRadius())
	{
		if (false == EnemyState_IdleBase::IsAttackerEmpty())
		{
			size_t RandomAttack = GetEnemyFsm()->GetRandomAttack();
			GetFSM()->ChangeState(RandomAttack);
		}

		//�÷��̾�� ������ ������ Idle�� �����ϰų� Attack ���·� ������
		return true;
	}

	return false;
}