#pragma once
#include "FieldLevelBase.h"

class SchoolEntryLevel : public FieldLevelBase
{
public:
	SchoolEntryLevel();
	~SchoolEntryLevel() override;

	SchoolEntryLevel(const SchoolEntryLevel& _Other) = delete;
	SchoolEntryLevel(SchoolEntryLevel&& _Other) noexcept = delete;
	SchoolEntryLevel& operator=(const SchoolEntryLevel& _Other) = delete;
	SchoolEntryLevel& operator=(const SchoolEntryLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

