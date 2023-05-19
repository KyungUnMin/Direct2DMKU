#pragma once
#include "EnemyStateBase.h"

class EnemyState_DamagedBase : public EnemyStateBase
{
public:
	EnemyState_DamagedBase();
	~EnemyState_DamagedBase() override;

	EnemyState_DamagedBase(const EnemyState_DamagedBase& _Other) = delete;
	EnemyState_DamagedBase(EnemyState_DamagedBase&& _Other) noexcept = delete;
	EnemyState_DamagedBase& operator=(const EnemyState_DamagedBase& _Other) = delete;
	EnemyState_DamagedBase& operator=(const EnemyState_DamagedBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	bool Update_BlowBack(float _DeltaTime);
	void ExitState() override;

	inline void SetBlowValue(float _StartAcc, float _Duration = 1.0f)
	{
		StartAcc = _StartAcc;
		Duration = _Duration;
	}

private:
	float StartAcc = 2000.f;
	float Duration = 1.0f;
	const float StartHeight = 100.f;

	bool PlayerDir = true;
	std::shared_ptr<class BackGround> BGPtr = nullptr;

	bool Update_BlowHorizon(float _Ratio, float _DeltaTime);
	void Update_BlowVertical(float _Ratio);
};

