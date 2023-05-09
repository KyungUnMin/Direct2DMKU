#pragma once
#include "EnemyStateBase.h"

class EnemyState_Idle : public EnemyStateBase
{
public:
	EnemyState_Idle();
	~EnemyState_Idle() override;

	EnemyState_Idle(const EnemyState_Idle& _Other) = delete;
	EnemyState_Idle(EnemyState_Idle&& _Other) noexcept = delete;
	EnemyState_Idle& operator=(const EnemyState_Idle& _Other) = delete;
	EnemyState_Idle& operator=(const EnemyState_Idle&& _Other) noexcept = delete;

protected:

private:

};

