#pragma once
#include "EnemyStateBase.h"

class EnemyFSMBase;
class FieldEnemyBase;
class EnemySpawner;

class EnemyState_WalkBase : public EnemyStateBase
{
public:
	EnemyState_WalkBase();
	virtual ~EnemyState_WalkBase() = 0;

	EnemyState_WalkBase(const EnemyState_WalkBase& _Other) = delete;
	EnemyState_WalkBase(EnemyState_WalkBase&& _Other) noexcept = delete;
	EnemyState_WalkBase& operator=(const EnemyState_WalkBase& _Other) = delete;
	EnemyState_WalkBase& operator=(const EnemyState_WalkBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) final;

	template <typename EnumType>
	inline void SetNextState(EnumType _ArriveState)
	{
		ArriveState = static_cast<size_t>(_ArriveState);
	}

private:
	std::pair<int, int> GridMapScale;

	class EnemySpawner* EnemySpawnerPtr = nullptr;
	std::vector<std::pair<int, int>> PathStack;
	float4 DestPos = float4::Zero;
	float4 StartPos = float4::Zero;

	float Timer = 0.f;
	const float MoveDuration = 0.1f;
	const float ReFindPathRange = 150.f;
	size_t ArriveState = -1;
	

	void FindPath();
	bool SetDest();
};

