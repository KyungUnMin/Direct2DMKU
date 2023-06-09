#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"

class EnemyFSMBase;
class FieldEnemyBase;
class GameEngineCollision;
class BackGround;
class EnemySpawner;

class EnemyStateBase : public StateBase
{
public:
	EnemyStateBase();
	virtual ~EnemyStateBase() = 0;

	EnemyStateBase(const EnemyStateBase& _Other) = delete;
	EnemyStateBase(EnemyStateBase&& _Other) noexcept = delete;
	EnemyStateBase& operator=(const EnemyStateBase& _Other) = delete;
	EnemyStateBase& operator=(const EnemyStateBase&& _Other) noexcept = delete;

	//공격에 반응하지 않는 슈퍼아머 상태인지 여부
	inline bool IsUnbeatable() const
	{
		return Unbeatable;
	}

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

	float4 GetVecToPlayer(const float4& _Pos, bool _Is2D = false);


	inline void SetSight(float _Radius)
	{
		SightRadius = _Radius;
	}

	inline float GetSightRadius() const
	{
		return SightRadius;
	}

	bool IsRightDir();



	//State가 시작될 때를 기준으로 점프
	void Update_SinJump(float _Duration, float _MaxHeight = 80.f);

	//Timer를 직접 넣어주는 점프
	void Update_SinJump(float _Timer, float _Duration, float _MaxHeight);

	//State가 시작될 때를 기준으로 점프(아래로 떨어지지 않음)
	void Update_SinHalfJump(float _Duration, float _MaxHeight = 80.f);

	//Timer를 직접 넣어주는 점프(아래로 떨어지지 않음)
	void Update_SinHalfJump(float _Timer, float _Duration, float _MaxHeight);


	//State가 시작될 때를 기준으로 착지(공중에서 시작)
	void Update_SinHalfFall(float _Duration, float _MaxHeight = 80.f);

	//Timer를 직접 넣어주는 착지(공중에서 시작)
	void Update_SinHalfFall(float _Timer, float _Duration, float _MaxHeight);




	bool Update_AccMove(
		float _DeltaTime, float _Ratio,
		const float4& _Dir, float _StartAcc = 2000.f);


	inline std::shared_ptr<BackGround> GetBackGround() const
	{
		return BGPtr;
	}

	//슈퍼아머 상태
	inline void SetUnbeatable()
	{
		Unbeatable = true;
	}

	//State가 전환시 플레이어를 향해 방향전환 하지 않는다
	inline void DontLookPlayer()
	{
		IsLookPlayer = false;
	}

	void OffMainCollider();
	void OnMainCollider();

	//인자로 받은 확률 만큼 FSM에서 지정한 원거리 공격을 수행한다
	bool FarAttackExcute(int _Percent);

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> MainCollider = nullptr;

	EnemyFSMBase* FsmPtr = nullptr;
	FieldEnemyBase* EnemyPtr = nullptr;
	std::shared_ptr<BackGround> BGPtr = nullptr;

	float SightRadius = 100.f;

	//슈퍼아머 상태여부
	bool Unbeatable = false;

	bool IsLookPlayer = true;


	inline void ValidCheck(void* _Ptr) const
	{
		if (nullptr != _Ptr)
			return;

		MsgAssert("EnemyState 자식쪽에서 EnemyStateBase::Start를 호출시켜주어야 합니다");
	}

};

