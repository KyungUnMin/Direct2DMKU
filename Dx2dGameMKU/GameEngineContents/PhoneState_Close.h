#pragma once
#include "PhoneStateBase.h"

class PhoneState_Close : public PhoneStateBase
{
public:
	PhoneState_Close();
	~PhoneState_Close() override;

	PhoneState_Close(const PhoneState_Close& _Other) = delete;
	PhoneState_Close(PhoneState_Close&& _Other) noexcept = delete;
	PhoneState_Close& operator=(const PhoneState_Close& _Other) = delete;
	PhoneState_Close& operator=(const PhoneState_Close&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	const float Duration = 0.5f;

};

