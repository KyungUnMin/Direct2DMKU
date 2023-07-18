#pragma once
#include "PhoneStateBase.h"

class PhoneState_Inventory : public PhoneStateBase
{
public:
	PhoneState_Inventory();
	~PhoneState_Inventory() override;

	PhoneState_Inventory(const PhoneState_Inventory& _Other) = delete;
	PhoneState_Inventory(PhoneState_Inventory&& _Other) noexcept = delete;
	PhoneState_Inventory& operator=(const PhoneState_Inventory& _Other) = delete;
	PhoneState_Inventory& operator=(const PhoneState_Inventory&& _Other) noexcept = delete;

protected:

private:

};

