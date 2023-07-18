#include "PrecompileHeader.h"
#include "PhoneFSM.h"

#include "PhoneState_Open.h"
#include "PhoneState_Weapon.h"
#include "PhoneState_Skill.h"
#include "PhoneState_Inventory.h"
#include "PhoneState_Close.h"


PhoneFSM::PhoneFSM()
{

}

PhoneFSM::~PhoneFSM()
{

}


void PhoneFSM::Init(HandPhoneUI* _Phone)
{
	Phone = _Phone;

	FSMBase::ResizeStates(PhoneStateType::COUNT);

	FSMBase::CreateState<PhoneState_Open>(PhoneStateType::Open);
	FSMBase::CreateState<PhoneState_Weapon>(PhoneStateType::Weapon);
	FSMBase::CreateState<PhoneState_Skill>(PhoneStateType::Skill);
	FSMBase::CreateState<PhoneState_Inventory>(PhoneStateType::Inventory);
	FSMBase::CreateState<PhoneState_Close>(PhoneStateType::Close);

	ChangeState(PhoneStateType::Weapon);
}

void PhoneFSM::ChangeState(PhoneStateType _NextState)
{
	FSMBase::ChangeState(_NextState);

	if (PhoneStateType::Open == _NextState)
		return;

	if (PhoneStateType::Close == _NextState)
		return;

	LastUserState = _NextState;
}