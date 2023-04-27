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

private:
	static const std::string_view MapImgName;
	static const float4 MapScale;

	void LoadImgRes();
};

