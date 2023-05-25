#include "PrecompileHeader.h"
#include "EnemyState_IdleBase.h"

#include <GameEngineBase/GameEngineRandom.h>


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