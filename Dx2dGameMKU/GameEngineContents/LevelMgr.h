#pragma once

enum class LevelNames
{
	OpeningLevel,
	EndingLevel_Win,
	EndingLevel_Lose,

	SchoolEntryLevel,
	SchoolBossLevel,
	CrossTownLevel1,
	CrossTownLevel2,
	CrossTownLevel3,
	TownBossLevel,
	OceanLevel,
	OceanBossLevel,

	Shop_BurgerLevel,
	Shop_StoreLevel,
	Shop_GymLevel
};

class LevelMgr
{
	friend class RCG_GameCore;

public:
	LevelMgr(const LevelMgr& _Other) = delete;
	LevelMgr(LevelMgr&& _Other) noexcept = delete;
	LevelMgr& operator=(const LevelMgr& _Other) = delete;
	LevelMgr& operator=(const LevelMgr&& _Other) noexcept = delete;

	static std::string_view EnumToString(LevelNames _Name)
	{
		size_t Index = static_cast<size_t>(_Name);
		if (IndexToString.size() <= Index)
		{
			MsgAssert("�ش� ������ �����ϴ� string�� ������� ���� �����ϴ�");
		}

		return IndexToString[static_cast<size_t>(_Name)];
	}

	static void ChangeLevel(LevelNames _Level);

	static LevelNames GetCurrentLevel()
	{
		return NowLevel;
	}

protected:

private:
	static const std::vector<std::string_view> IndexToString;
	static LevelNames NowLevel;


	static void CreateLevel(LevelNames _StartLevel);

	LevelMgr();
	virtual ~LevelMgr() = 0;
};

