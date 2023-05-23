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
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const std::vector<float4> DestSitPos;


	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDesks();
	void CreateDoors();
	void CreateEnemies();
};

