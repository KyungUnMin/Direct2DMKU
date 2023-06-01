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
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const std::vector<float4> EnemySpawnPoses;
	static const std::vector<class NpcCreateInfo> NpcInfoes;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
	void CreateEnemies();
};

