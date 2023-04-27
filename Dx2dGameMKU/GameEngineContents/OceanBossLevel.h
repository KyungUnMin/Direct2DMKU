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

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

