#pragma once
#include "EnemyStateBase.h"
#include "SoundMgr.h"

enum class MoneyType;

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

	//������ �¾� ���󰡱�
	bool Update_BlowBack(float _DeltaTime);
	//������ �¾� ���󰡱� + ���� ƨ���� ������
	void Update_BlowReflect(float _DeltaTime);

	void ExitState() override;

	inline void SetBlowValue(float _StartAcc, float _Duration = 1.0f)
	{
		StartAcc = _StartAcc;
		Duration = _Duration;
	}

	//���󰥶� ���� �پ ���󰡱� ����
	inline void SetGroundBlow()
	{
		IsHeightFix = true;
	}

	//Update_BlowBack�� ȣ��� ���󰡴� ���� ����
	inline void Set_BlowDir(bool _IsRight)
	{
		//Update_BlowHorizon���� Enemy�� �ݴ� �������� ���󰡱� ����
		EnemyDir = !_IsRight;
	}

	//Enemy�� ��ġ�� _MoneyŸ�� Money�� ����
	void CreateMoney(MoneyType _Money);

	//Enemy�� ��ġ�� ����Ÿ�� Money�� ����
	void CreateMoney();

	//_Duration�������� Enemy�� ��ġ�� ����Ÿ�� Money�� �����Ѵ�
	void Update_Money(float _DeltaTime, float _Duration = 0.5f);

private:
	float StartAcc = 2000.f;
	float Duration = 1.0f;
	const float StartHeight = 100.f;
	bool IsHeightFix = false;
	bool IsWallHit = false;


	bool EnemyDir = true;
	float MoneyTimer = 0.f;

	void Update_BlowVertical(float _Ratio);
	bool Update_BlowHorizon(float _Ratio, float _DeltaTime);
	void CreateWallEffect();
};

