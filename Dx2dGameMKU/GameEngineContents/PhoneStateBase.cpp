#include "PrecompileHeader.h"
#include "PhoneStateBase.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"

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

std::shared_ptr<GameEngineUIRenderer> PhoneStateBase::CreateRender(const std::string_view& _TexName /*= ""*/)
{
	std::shared_ptr<GameEngineUIRenderer> Render = nullptr;

	Render = PhonePtr->CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Phone);

	if (false == _TexName.empty())
	{
		Render->SetScaleToTexture(_TexName);
	}

	Render->Off();

	return Render;
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

PhoneStateType PhoneStateBase::GetPrevUserState()
{
	return PhoneFsmPtr->GetLastUserState();
}

