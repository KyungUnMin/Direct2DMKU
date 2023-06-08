#pragma once
#include "EnemyState_AttackBase.h"

class BossState_AttackBase : public EnemyState_AttackBase
{
public:
	BossState_AttackBase();
	~BossState_AttackBase() override;

	BossState_AttackBase(const BossState_AttackBase& _Other) = delete;
	BossState_AttackBase(BossState_AttackBase&& _Other) noexcept = delete;
	BossState_AttackBase& operator=(const BossState_AttackBase& _Other) = delete;
	BossState_AttackBase& operator=(const BossState_AttackBase&& _Other) noexcept = delete;

protected:

	//�÷��̾��� ���� �̵� ��ġ�� ��ȯ
	float4 GetExpectPlayerPos();


private:

};

