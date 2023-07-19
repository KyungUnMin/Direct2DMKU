#pragma once
#include "PhoneStateBase.h"

class GameEngineUIRenderer;

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
	static const std::vector<float4> CursorPoses;
	static bool IsEquipKnuckle;
	static bool IsEquipWatch;
	static int KnuckleDamage;

	size_t NowCursorIndex = 0;

	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Info_Knuckle = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Info_Watch = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Equip_Knuckle = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Equip_Watch = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Equip_All = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Equip_Nothing = nullptr;

	std::shared_ptr<GameEngineUIRenderer> CreateRender(const std::string_view& _TexName);


	void SelectEquipRender();
	void MoveCursorRender();


	bool Update_Equip();
	void Update_MoveCursor();
};

