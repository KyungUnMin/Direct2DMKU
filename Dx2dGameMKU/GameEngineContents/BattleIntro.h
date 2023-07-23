#pragma once
#include "UIBase.h"

class GameEngineUIRenderer;

class BattleIntro : public UIBase
{
public:
	BattleIntro();
	~BattleIntro() override;

	BattleIntro(const BattleIntro& _Other) = delete;
	BattleIntro(BattleIntro&& _Other) noexcept = delete;
	BattleIntro& operator=(const BattleIntro& _Other) = delete;
	BattleIntro& operator=(const BattleIntro&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Ani_FileName;

	std::shared_ptr<GameEngineUIRenderer> Render = nullptr;

	void LoadImgRes();
	void CreateAnimation();

};

