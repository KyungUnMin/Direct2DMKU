#pragma once
#include "EnemyStateBase.h"

class EnemyState_AttackBase : public EnemyStateBase
{
public:
	EnemyState_AttackBase();
	~EnemyState_AttackBase() override;

	EnemyState_AttackBase(const EnemyState_AttackBase& _Other) = delete;
	EnemyState_AttackBase(EnemyState_AttackBase&& _Other) noexcept = delete;
	EnemyState_AttackBase& operator=(const EnemyState_AttackBase& _Other) = delete;
	EnemyState_AttackBase& operator=(const EnemyState_AttackBase&& _Other) noexcept = delete;

protected:
	//_AniName �ִϸ��̼�, _Index��° �����ӿ� �÷��̾�� �浹 üũ�� �ϰڴ�
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index);

	//�� Enemy�� Collision Transform �� ����
	void SetAttackColValue(const float4& _Offset, const float4& _Scale = float4{100.f, 100.f, 100.f});

	//�÷��̾�� �浹������ ó���ؾ� �ϴ� ��Ȳ
	virtual void Attack() = 0;


private:



	void AttackCheck();
};

