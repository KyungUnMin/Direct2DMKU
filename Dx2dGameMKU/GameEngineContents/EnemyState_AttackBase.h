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

	void MoveOn()
	{
		IsMovingAttack = true;
		MoveStartTime = GetLiveTime();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	//_AniName 애니메이션, _Index번째 프레임에 플레이어와 충돌 체크를 하겠다
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index);

	//이 Enemy의 Collision Transform 값 변경
	void SetAttackColValue(const float4& _Offset = float4{50.f, 0.f, 0.f}, const float4& _Scale = float4{100.f, 100.f, 100.f});

	//플레이어와 충돌했을때 처리해야 하는 상황
	virtual void Attack() = 0;



	void SetMoveEvent(const std::string_view& _AniName, size_t _MoveStartFrame,
		bool _IsReverseDir = false, float _MoveDuration = 0.5f, float _StartAcc = 1000.f);

private:
	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	//True면 오른쪽, false면 왼쪽
	bool EnemyDir = false;

	//움직이는 공격여부
	bool IsMovingAttack = false;
	//움직이는 공격일때 역방향으로 움직이는지 여부
	bool IsReverseMoveDir = false;

	//움직이는 공격일때 시작 속도
	float StartAcc = 1000.f;
	//움직이기 시작한 시간
	float MoveStartTime = 0.0f;

	float MoveDuration = 0.5f;

	void AttackCheck();
};

