#pragma once
#include "PhoneStateBase.h"

class PhoneState_Open : public PhoneStateBase
{
public:
	static const float4 StartOffset;// = float4{ -300.f, -400.f };
	static const float4 DestOffset;// = float4{ -300.f, 0.f };

	PhoneState_Open();
	~PhoneState_Open() override;

	PhoneState_Open(const PhoneState_Open& _Other) = delete;
	PhoneState_Open(PhoneState_Open&& _Other) noexcept = delete;
	PhoneState_Open& operator=(const PhoneState_Open& _Other) = delete;
	PhoneState_Open& operator=(const PhoneState_Open&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	const float Duration = 0.5f;
	
};

