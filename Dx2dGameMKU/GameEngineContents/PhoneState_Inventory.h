#pragma once
#include "PhoneStateBase.h"

class GameEngineUIRenderer;

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
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const std::vector<float4> Positions;
	static const std::vector<std::string_view> ItemTexNames;
	
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> ItemRenders;

	size_t NowCursorIndex = 0;

	void CursorRenderMove();
	void SettingItemUI();

	void Update_CursorMove();
};

