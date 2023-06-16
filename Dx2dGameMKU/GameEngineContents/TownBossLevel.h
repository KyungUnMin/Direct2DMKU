#pragma once
#include "FieldLevelBase.h"

class GameEngineSpriteRenderer;

class TownBossLevel : public FieldLevelBase
{
public:
	TownBossLevel();
	~TownBossLevel() override;

	TownBossLevel(const TownBossLevel& _Other) = delete;
	TownBossLevel(TownBossLevel&& _Other) noexcept = delete;
	TownBossLevel& operator=(const TownBossLevel& _Other) = delete;
	TownBossLevel& operator=(const TownBossLevel&& _Other) noexcept = delete;

	inline std::shared_ptr<GameEngineSpriteRenderer> GetNightBackImg() const
	{
		if (nullptr == NightBackImg)
		{
			MsgAssert("TownBossLevel에서 밤 이미지를 만들어주지 않았습니다");
		}

		return NightBackImg;
	}

protected:
	void Start() override;
	void LevelChangeStart() override;

private:
	//<텍스처 이름, 오프셋>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const float4 PlayerStartPos;
	static const std::string_view Night_FileName;

	std::shared_ptr<GameEngineSpriteRenderer> NightBackImg = nullptr;


	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
};

