#pragma once
#include "FieldLevelBase.h"

class OceanBossLevel : public FieldLevelBase
{
public:
	OceanBossLevel();
	~OceanBossLevel() override;

	OceanBossLevel(const OceanBossLevel& _Other) = delete;
	OceanBossLevel(OceanBossLevel&& _Other) noexcept = delete;
	OceanBossLevel& operator=(const OceanBossLevel& _Other) = delete;
	OceanBossLevel& operator=(const OceanBossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart() override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::vector<std::string_view> AniPathes;

	static const std::string_view CollisionImageName;
	static const float4 PlayerStartPos;

	std::shared_ptr<class FieldEnemy_Noise> Boss_Noise = nullptr;


	void LoadImgRes();
	void CreateBackGrounds();
	void CreateAnimation(
		const std::string_view& _AniPath, 
		const float4& _Scale, 
		const float4& _Pos,
		bool _GuiSelect);
};

