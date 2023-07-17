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
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	//<�ؽ�ó �̸�, ������>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const std::vector<float4> EnemySpawnPoses;
	static const std::vector<class NpcCreateInfo> NpcInfoes;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoor_ForDebug();
	void CreateDoor();
	void CreateEnemies();
	void CreateWaveRender();
};

