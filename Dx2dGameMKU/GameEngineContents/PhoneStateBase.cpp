#include "PrecompileHeader.h"
#include "PhoneStateBase.h"

#include "PhoneFSM.h"
#include "HandPhoneUI.h"


PhoneStateBase::PhoneStateBase()
{

}

PhoneStateBase::~PhoneStateBase()
{

}

void PhoneStateBase::Start()
{
	StateBase::Start();

	PhoneFsmPtr = GetConvertFSM<PhoneFSM>();
	if (nullptr == PhoneFsmPtr)
	{
		MsgAssert("해당 State가 PhoneFSM에 속해있지 않습니다");
		return;
	}

	PhonePtr = PhoneFsmPtr->GetPhone();
}


bool PhoneStateBase::IsUserState(PhoneStateType _State)
{
	if (PhoneStateType::Inventory == _State)
		return true;

	if (PhoneStateType::Skill == _State)
		return true;
	
	if (PhoneStateType::Weapon == _State)
		return true;

	return false;
}