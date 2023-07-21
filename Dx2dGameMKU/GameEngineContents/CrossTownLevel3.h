#pragma once
#include "FieldLevelBase.h"

class CrossTownLevel3 : public FieldLevelBase
{
public:
	inline static void OpenTownBossDoor()
	{
		IsTownBossDoorOpen = true;
	}

	CrossTownLevel3();
	~CrossTownLevel3() override;

	CrossTownLevel3(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3(CrossTownLevel3&& _Other) noexcept = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3& _Other) = delete;
	CrossTownLevel3& operator=(const CrossTownLevel3&& _Other) noexcept = delete;


protected:
	void Start() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const std::vector<float4> EnemySpawnPoses;
	static const std::vector<class NpcCreateInfo> NpcInfoes;
	static bool IsTownBossDoorOpen;

	std::shared_ptr<class FieldDoor> TownBossDoor = nullptr;
	std::shared_ptr<class EventArea> EventPtr = nullptr;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
	void CreateEnemies();
	void CreateScreenLock();
	void CreateTutorialArea();
};

