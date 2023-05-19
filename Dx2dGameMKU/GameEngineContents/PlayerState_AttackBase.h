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
	

	//_AniName 애니메이션, _Index번째 프레임에 플레이어와 충돌 체크를 하겠다
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index);

	
	//이 Player의 Collision Transform 값 변경
	void SetAttackColValue(const float4& _Offset = float4{50.f, 0.f, 0.f}, const float4& _Scale = float4{ 100.f, 100.f, 100.f });


	//적과 충돌했을때 처리해야 하는 상황
	virtual void Attack(class FieldEnemyBase* _Enemy) = 0;

private:
	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	void AttackCheck();
};

