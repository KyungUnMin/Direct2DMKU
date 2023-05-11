#pragma once
#include "FieldActorBase.h"
#include "EnemyFSM.h"

class GameEngineSpriteRenderer;

class FieldEnemyBase : public FieldActorBase
{
public:
	FieldEnemyBase();
	~FieldEnemyBase() override;

	FieldEnemyBase(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase(FieldEnemyBase&& _Other) noexcept = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	void Render(float _DeltaTime) final;

	template <typename StateType>
	std::shared_ptr<StateType> CreateState(EnemyStateType _Index)
	{
		return Fsm.CreateState<StateType>(_Index);
	}

	void ChangeState(EnemyStateType _Index)
	{
		Fsm.ChangeState(_Index);
	}

private:
	EnemyFSM Fsm;
};

