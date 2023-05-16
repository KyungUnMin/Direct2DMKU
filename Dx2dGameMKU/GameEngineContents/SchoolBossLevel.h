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
	void Update(float _DeltaTime) override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;

	void LoadImgRes();
	void CreatBackGrounds();
	void CreateDoors();
};

