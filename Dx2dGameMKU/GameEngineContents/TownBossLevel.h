#pragma once
#include "FieldLevelBase.h"

class TownBossLevel : public FieldLevelBase
{
public:
	TownBossLevel();
	~TownBossLevel() override;

	TownBossLevel(const TownBossLevel& _Other) = delete;
	TownBossLevel(TownBossLevel&& _Other) noexcept = delete;
	TownBossLevel& operator=(const TownBossLevel& _Other) = delete;
	TownBossLevel& operator=(const TownBossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart() override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const float4 PlayerStartPos;

	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
};

