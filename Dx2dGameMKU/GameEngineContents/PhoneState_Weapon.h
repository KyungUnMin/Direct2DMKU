#pragma once
#include "PhoneStateBase.h"

class PhoneState_Weapon : public PhoneStateBase
{
public:
	PhoneState_Weapon();
	~PhoneState_Weapon() override;

	PhoneState_Weapon(const PhoneState_Weapon& _Other) = delete;
	PhoneState_Weapon(PhoneState_Weapon&& _Other) noexcept = delete;
	PhoneState_Weapon& operator=(const PhoneState_Weapon& _Other) = delete;
	PhoneState_Weapon& operator=(const PhoneState_Weapon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	size_t NowCursorIndex = 0;
	static const std::vector<float4> CursorPoses;

	std::shared_ptr<class GameEngineUIRenderer> Cursor = nullptr;


	void MoveCursorRender();
};

