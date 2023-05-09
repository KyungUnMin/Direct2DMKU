#pragma once
#include "FSMBase.h"

class EnemyFSM : public FSMBase
{
public:
	EnemyFSM();
	~EnemyFSM() override;

	EnemyFSM(const EnemyFSM& _Other) = delete;
	EnemyFSM(EnemyFSM&& _Other) noexcept = delete;
	EnemyFSM& operator=(const EnemyFSM& _Other) = delete;
	EnemyFSM& operator=(const EnemyFSM&& _Other) noexcept = delete;

protected:

private:

};

