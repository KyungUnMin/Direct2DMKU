#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"

class EnemyFSMBase;
class FieldEnemyBase;
class GameEngineCollision;

class EnemyStateBase : public StateBase
{
public:
	EnemyStateBase();
	virtual ~EnemyStateBase() = 0;

	EnemyStateBase(const EnemyStateBase& _Other) = delete;
	EnemyStateBase(EnemyStateBase&& _Other) noexcept = delete;
	EnemyStateBase& operator=(const EnemyStateBase& _Other) = delete;
	EnemyStateBase& operator=(const EnemyStateBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;


	inline EnemyFSMBase* GetEnemyFsm() const
	{
		ValidCheck(FsmPtr);
		return FsmPtr;
	}

	inline FieldEnemyBase* GetEnemy() const
	{
		ValidCheck(EnemyPtr);
		return EnemyPtr;
	}

	inline std::shared_ptr<GameEngineSpriteRenderer> GetRenderer() const
	{
		ValidCheck(Renderer.get());
		return Renderer;
	}

	void ChangeRenderDirection();

	float4 GetVecToPlayer(bool Is2D = false);

	inline void SetSight(float _Radius)
	{
		SightRadius = _Radius;
	}

	inline float GetSightRadius() const
	{
		return SightRadius;
	}

	bool IsRightDir();

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> MainCollider = nullptr;

	EnemyFSMBase* FsmPtr = nullptr;
	FieldEnemyBase* EnemyPtr = nullptr;
	float SightRadius = 100.f;

	inline void ValidCheck(void* _Ptr) const
	{
		if (nullptr != _Ptr)
			return;

		MsgAssert("EnemyState 자식쪽에서 EnemyStateBase::Start를 호출시켜주어야 합니다");
	}

};

