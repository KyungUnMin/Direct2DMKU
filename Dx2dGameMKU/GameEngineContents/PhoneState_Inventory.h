#pragma once
#include "PhoneStateBase.h"

#include <GameEngineCore/GameEngineFont.h>

class GameEngineUIRenderer;
class UIFontRenderer;
enum class InvenItemType;

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
	static const std::vector<std::string_view> EatSfxs;
	static const float4 DataTextColor;
	static const float4 PreviewTextColor;
	
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
	std::vector<std::pair<InvenItemType, std::shared_ptr<GameEngineUIRenderer>>> ItemRenders;

	enum class DataTextType
	{
		Level,
		Exp,
		RemainExp,
		HP,
		MP,
		AP,
		SP,

		COUNT
	};

	std::vector<std::shared_ptr<UIFontRenderer>> PlayerDataTexts;
	size_t NowCursorIndex = 0;

	struct PlayerData
	{
		int PlayerLevel = 0;
		int PlayerExp = 0;
		int RestExp = 0;

		int PlayerHealthPoint = 0;
		int PlayerMagicPoint = 0;
		int PlayerAttackPoint = 0;
		int PlayerSP = 0;
	};

	PlayerData OriginData;
	PlayerData PreviewData;


	void CreateTextRender(
		DataTextType _Type,
		FW1_TEXT_FLAG _Align, 
		const float4& _Offset = float4::Zero,
		const float4& _Color = float4::White,
		float _Scale = 20.f);

	void CursorRenderMove();
	void SettingItemUI();
	void SettingOriginDataRender();
	void SettingPreviewDataRender();
	void SettingPlayerDataRender(const PlayerData& _Data);

	bool Update_Eat();
	void Update_CursorMove();
};

