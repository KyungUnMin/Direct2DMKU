#pragma once
#include "PlayerStateBase.h"

class PlayerState_AttackBase : public PlayerStateBase
{
public:
	PlayerState_AttackBase();
	~PlayerState_AttackBase() override;

	PlayerState_AttackBase(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase(PlayerState_AttackBase&& _Other) noexcept = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	

	//_AniName �ִϸ��̼�, _Index��° �����ӿ� �÷��̾�� �浹 üũ�� �ϰڴ�
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index);

	
	//�� Player�� Collision Transform �� ����
	void SetAttackColValue(const float4& _Offset = float4{50.f, 0.f, 0.f}, const float4& _Scale = float4{ 100.f, 100.f, 100.f });


	//���� �浹������ ó���ؾ� �ϴ� ��Ȳ
	virtual void Attack(class FieldEnemyBase* _Enemy) = 0;

private:
	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	void AttackCheck();
};

