#pragma once
#include "FieldLevelBase.h"

class CrossTownLevel3 : public FieldLevelBase
{
public:
	CrossTownLevel3();
	~CrossTownLevel3() override;

	CrossTownLevel3(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3(CrossTownLevel3&& _Other) noexcept = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const std::vector<float4> EnemySpawnPoses;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
	void CreateEnemies();
};

