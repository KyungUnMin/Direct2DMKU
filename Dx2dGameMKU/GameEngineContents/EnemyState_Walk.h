#pragma once
#include "EnemyStateBase.h"

class EnemyFSM;
class FieldEnemyBase;

class EnemyState_Walk : public EnemyStateBase
{
public:
	EnemyState_Walk();
	~EnemyState_Walk() override;

	EnemyState_Walk(const EnemyState_Walk& _Other) = delete;
	EnemyState_Walk(EnemyState_Walk&& _Other) noexcept = delete;
	EnemyState_Walk& operator=(const EnemyState_Walk& _Other) = delete;
	EnemyState_Walk& operator=(const EnemyState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	EnemyFSM* FsmPtr = nullptr;
	FieldEnemyBase* EnemyPtr = nullptr;
	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::pair<int, int> GridMapScale;

	std::vector<std::pair<int, int>> PathStack;
	float4 DestPos = float4::Zero;
	float4 StartPos = float4::Zero;
	float Timer = 0.f;
	const float MoveDuration = 0.1f;

	void FindPath();
	bool SetDest();
};

