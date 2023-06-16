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
			MsgAssert("TownBossLevel���� �� �̹����� ��������� �ʾҽ��ϴ�");
		}

		return NightBackImg;
	}

protected:
	void Start() override;
	void LevelChangeStart() override;

private:
	//<�ؽ�ó �̸�, ������>
	static const std::vector<std::pair<std::string_view, float4>> BGInfoes;
	static const std::string_view CollisionImageName;
	static const float4 PlayerStartPos;
	static const std::string_view Night_FileName;

	std::shared_ptr<GameEngineSpriteRenderer> NightBackImg = nullptr;


	void LoadImgRes();
	void CreateBackGrounds();
	void CreateDoors();
};

