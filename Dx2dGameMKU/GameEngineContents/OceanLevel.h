#pragma once
#include "FieldLevelBase.h"

class OceanLevel : public FieldLevelBase
{
public:
	OceanLevel();
	~OceanLevel() override;

	OceanLevel(const OceanLevel& _Other) = delete;
	OceanLevel(OceanLevel&& _Other) noexcept = delete;
	OceanLevel& operator=(const OceanLevel& _Other) = delete;
	OceanLevel& operator=(const OceanLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

