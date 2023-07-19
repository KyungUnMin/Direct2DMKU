#pragma once
#include "StateBase.h"



class HandPhoneUI;
class PhoneFSM;
enum class PhoneStateType;
class GameEngineUIRenderer;

class PhoneStateBase : public StateBase
{
public:
	PhoneStateBase();
	virtual ~PhoneStateBase() = 0;

	PhoneStateBase(const PhoneStateBase& _Other) = delete;
	PhoneStateBase(PhoneStateBase&& _Other) noexcept = delete;
	PhoneStateBase& operator=(const PhoneStateBase& _Other) = delete;
	PhoneStateBase& operator=(const PhoneStateBase&& _Other) noexcept = delete;

protected:
	void Start() override;

	inline PhoneFSM* GetPhoneFSM() const
	{
		return PhoneFsmPtr;
	}

	HandPhoneUI* GetPhone() const
	{
		return PhonePtr;
	}

	std::shared_ptr<GameEngineUIRenderer> CreateRender(const std::string_view& _TexName = "");


	bool IsUserState(PhoneStateType _State);

private:
	PhoneFSM* PhoneFsmPtr = nullptr;
	HandPhoneUI* PhonePtr = nullptr;
};

