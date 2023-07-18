#pragma once
#include "FSMBase.h"

enum class PhoneStateType
{
	Open,
	Weapon,
	Skill,
	Inventory, 
	Close,

	COUNT
};

class HandPhoneUI;

class PhoneFSM : public FSMBase
{
public:
	PhoneFSM();
	~PhoneFSM() override;

	PhoneFSM(const PhoneFSM& _Other) = delete;
	PhoneFSM(PhoneFSM&& _Other) noexcept = delete;
	PhoneFSM& operator=(const PhoneFSM& _Other) = delete;
	PhoneFSM& operator=(const PhoneFSM&& _Other) noexcept = delete;

	void Init(HandPhoneUI* _Phone);

	inline HandPhoneUI* GetPhone() const
	{
		return Phone;
	}

	void ChangeState(PhoneStateType _NextState);

	inline PhoneStateType GetLastUserState() const
	{
		return LastUserState;
	}

protected:
	

private:
	HandPhoneUI* Phone = nullptr;

	//무기창, 스킬창, 인벤토리 중에 마지막으로 사용했던 State
	PhoneStateType LastUserState = PhoneStateType::COUNT;
};

