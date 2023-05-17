#pragma once
#include "FSMBase.h"

class FieldEnemyBase;

class EnemyFSMBase : public FSMBase
{
public:
	EnemyFSMBase();
	virtual ~EnemyFSMBase() = 0;

	EnemyFSMBase(const EnemyFSMBase& _Other) = delete;
	EnemyFSMBase(EnemyFSMBase&& _Other) noexcept = delete;
	EnemyFSMBase& operator=(const EnemyFSMBase& _Other) = delete;
	EnemyFSMBase& operator=(const EnemyFSMBase&& _Other) noexcept = delete;

	FieldEnemyBase* GetEnemy() const;

	virtual inline void Init(FieldEnemyBase* _Enemy)
	{
		Enemy = _Enemy;
	}

protected:

	


private:
	FieldEnemyBase* Enemy = nullptr;
};

