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

private:

};

