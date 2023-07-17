#pragma once
#include "UIBase.h"

class GameEngineUIRenderer;
enum class PlayerStateType;

class LevelUpUICtrl : public UIBase
{
public:
	LevelUpUICtrl();
	~LevelUpUICtrl() override;

	LevelUpUICtrl(const LevelUpUICtrl& _Other) = delete;
	LevelUpUICtrl(LevelUpUICtrl&& _Other) noexcept = delete;
	LevelUpUICtrl& operator=(const LevelUpUICtrl& _Other) = delete;
	LevelUpUICtrl& operator=(const LevelUpUICtrl&& _Other) noexcept = delete;

	void Off() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	static const std::string_view GrowthInfo_FileName;
	static const std::string_view NewSkillBoard_FileName;
	static const std::vector<std::string_view> AcquireSkillNames;

	//È¹µæ ·¹º§, È¹µæ  ½ºÅ³
	static std::vector<std::pair<int, PlayerStateType>> LevelUpSkills;

	static const std::pair<float4, float4> GrowBoxPoses;

	std::shared_ptr<GameEngineUIRenderer> GrowthBox = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NewSkillBox = nullptr;
	std::shared_ptr<class UIFontRenderer> LevelText = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NewSkillInfoText = nullptr;

	void LoadImageRes();
	void CreateGrowInfoRender();
	void CreateNewSkillBoardRender();
	void CreateLevelText();
	void CreateSkillInfoText();
	//void CreateNewSkillInfo();
	bool LevelUpCallBack();

	void Update_GrowthInfo(float _DeltaTime);
	void Update_NewSkill(float _DeltaTime);
};

