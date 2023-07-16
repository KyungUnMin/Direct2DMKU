#pragma once
#include "UIBase.h"

class GameEngineUIRenderer;
class UIFontRenderer;

class HUD : public UIBase
{
public:
	HUD();
	~HUD() override;

	HUD(const HUD& _Other) = delete;
	HUD(HUD&& _Other) noexcept = delete;
	HUD& operator=(const HUD& _Other) = delete;
	HUD& operator=(const HUD&& _Other) noexcept = delete;

	void UseShopMode();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct MpDatas
	{
		float NowMpRatio = 0.f;
		float PrevMpRatio = 0;
		float DestMpRatio = 0;
		int DestMp = 0;
	};

	static MpDatas MpData;
	static MpDatas ExpData;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> HealthBlocks;
	float MpTimer = 0.f;
	float ExpTimer = 0.f;
	std::shared_ptr <UIFontRenderer> MoneyText = nullptr;
	std::shared_ptr <UIFontRenderer> LevelText = nullptr;

	std::shared_ptr<GameEngineUIRenderer> FieldBackGround = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ShopBackGround = nullptr;

	void LoadImageRes();
	void CreateBackGround();
	void CreateShopBackGround();
	void CreateHpBar();
	void CreateMpBar();
	void CreateExpBar();
	void CreateMoneyText();
	void CreateLevelText();


	void Update_Hp();
	void Update_Mp(float _DeltaTime);
	void Update_Exp(float _DeltaTime);
	void Update_Money();
};

