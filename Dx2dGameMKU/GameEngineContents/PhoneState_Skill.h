#pragma once
#include "PhoneStateBase.h"

class PhoneState_Skill : public PhoneStateBase
{
public:
	PhoneState_Skill();
	~PhoneState_Skill() override;

	PhoneState_Skill(const PhoneState_Skill& _Other) = delete;
	PhoneState_Skill(PhoneState_Skill&& _Other) noexcept = delete;
	PhoneState_Skill& operator=(const PhoneState_Skill& _Other) = delete;
	PhoneState_Skill& operator=(const PhoneState_Skill&& _Other) noexcept = delete;

protected:

private:

};

