#pragma once
#include "UIBase.h"

class BossHUD : public UIBase
{
public:
	BossHUD();
	~BossHUD() override;

	BossHUD(const BossHUD& _Other) = delete;
	BossHUD(BossHUD&& _Other) noexcept = delete;
	BossHUD& operator=(const BossHUD& _Other) = delete;
	BossHUD& operator=(const BossHUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::vector<std::string_view> FileNames;

	float4 HpRatio = float4::Right;



	void ImageLoad();
	void CreateRenders();
};

//898 120 ResScale
