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
	void EnterState() override;

	//공격을 맞아 날라가기
	bool Update_BlowBack(float _DeltaTime);
	//공격을 맞아 날라가기 + 벽에 튕겨져 나오기
	void Update_BlowReflect(float _DeltaTime);

	void ExitState() override;

	inline void SetBlowValue(float _StartAcc, float _Duration = 1.0f)
	{
		StartAcc = _StartAcc;
		Duration = _Duration;
	}

	//날라갈때 땅에 붙어서 날라가기 설정
	inline void SetGroundBlow()
	{
		IsHeightFix = true;
	}

	//Update_BlowBack을 호출시 날라가는 방향 설정
	inline void Set_BlowDir(bool _IsRight)
	{
		//Update_BlowHorizon에서 Enemy의 반대 방향으로 날라가기 때문
		EnemyDir = !_IsRight;
	}


private:
	float StartAcc = 2000.f;
	float Duration = 1.0f;
	const float StartHeight = 100.f;
	bool IsHeightFix = false;
	bool IsWallHit = false;


	bool EnemyDir = true;

	void Update_BlowVertical(float _Ratio);
	bool Update_BlowHorizon(float _Ratio, float _DeltaTime);
	void CreateWallEffect();
};

