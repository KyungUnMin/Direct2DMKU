#pragma once
#include "FieldLevelBase.h"

class SchoolBossLevel : public FieldLevelBase
{
public:
	SchoolBossLevel();
	~SchoolBossLevel() override;

	SchoolBossLevel(const SchoolBossLevel& _Other) = delete;
	SchoolBossLevel(SchoolBossLevel&& _Other) noexcept = delete;
	SchoolBossLevel& operator=(const SchoolBossLevel& _Other) = delete;
	SchoolBossLevel& operator=(const SchoolBossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

