#pragma once
#include "EnemyStateBase.h"

class EnemyFSM;
class FieldEnemyBase;

class EnemyState_Walk : public EnemyStateBase
{
public:
	EnemyState_Walk();
	~EnemyState_Walk() override;

	EnemyState_Walk(const EnemyState_Walk& _Other) = delete;
	EnemyState_Walk(EnemyState_Walk&& _Other) noexcept = delete;
	EnemyState_Walk& operator=(const EnemyState_Walk& _Other) = delete;
	EnemyState_Walk& operator=(const EnemyState_Walk&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	EnemyFSM* FsmPtr = nullptr;
	FieldEnemyBase* EnemyPtr = nullptr;
};

