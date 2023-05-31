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
	static const std::string_view CollisionImageName;

	void LoadImgRes();
	void CreateBackGrounds();
};

