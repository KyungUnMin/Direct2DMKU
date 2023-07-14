#pragma once
#include "UIBase.h"

class GameEngineUIRenderer;

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

	std::vector<std::shared_ptr<GameEngineUIRenderer>> HealthBlocks;
	float Timer = 0.f;
	std::shared_ptr <class  UIFontRenderer> MoneyText = nullptr;

	std::shared_ptr<GameEngineUIRenderer> FieldBackGround = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ShopBackGround = nullptr;

	void LoadImageRes();
	void CreateBackGround();
	void CreateShopBackGround();
	void CreateHpBar();
	void CreateMpBar();
	void CreateMoneyText();

	void Update_Hp();
	void Update_Mp(float _DeltaTime);
	void Update_Money();
};

