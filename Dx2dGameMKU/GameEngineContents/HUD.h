#pragma once
#include "UIBase.h"

class HUD : public UIBase
{
public:
	HUD();
	~HUD() override;

	HUD(const HUD& _Other) = delete;
	HUD(HUD&& _Other) noexcept = delete;
	HUD& operator=(const HUD& _Other) = delete;
	HUD& operator=(const HUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> HealthBlocks;

	void LoadImageRes();
	void CreateBackGround();
	void CreateHealth();
};

