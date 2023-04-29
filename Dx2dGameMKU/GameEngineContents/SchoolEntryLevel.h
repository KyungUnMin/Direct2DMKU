#pragma once
#include "FieldLevelBase.h"

class SchoolEntryLevel : public FieldLevelBase
{
public:
	static const float4 LevelAreaScale;

	SchoolEntryLevel();
	~SchoolEntryLevel() override;

	SchoolEntryLevel(const SchoolEntryLevel& _Other) = delete;
	SchoolEntryLevel(SchoolEntryLevel&& _Other) noexcept = delete;
	SchoolEntryLevel& operator=(const SchoolEntryLevel& _Other) = delete;
	SchoolEntryLevel& operator=(const SchoolEntryLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
};

