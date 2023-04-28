#include "PrecompileHeader.h"
#include "LevelMgr.h"

#include <GameEngineCore/GameEngineCore.h>

#include "OpeningLevel.h"
#include "SchoolEntryLevel.h"
#include "SchoolBossLevel.h"
#include "CrossTownLevel1.h"
#include "CrossTownLevel2.h"
#include "CrossTownLevel3.h"
#include "TownBossLevel.h"
#include "OceanLevel.h"
#include "OceanBossLevel.h"

#include "Shop_BurgerLevel.h"
#include "Shop_StoreLevel.h"
#include "Shop_GymLevel.h"


const std::vector<std::string_view> LevelMgr::IndexToString =
{
	"OpeningLevel",
	"SchoolEntryLevel",
	"SchoolBossLevel",
	"CrossTownLevel1",
	"CrossTownLevel2",
	"CrossTownLevel3",
	"TownBossLevel",
	"OceanLevel",
	"OceanBossLevel",

	"Shop_BurgerLevel",
	"Shop_StoreLevel",
	"Shop_GymLevel"
};

LevelNames LevelMgr::NowLevel = LevelNames::OpeningLevel;

void LevelMgr::CreateLevel(LevelNames _StartLevel)
{
	GameEngineCore::CreateLevel<OpeningLevel>();
	GameEngineCore::CreateLevel<SchoolEntryLevel>();
	GameEngineCore::CreateLevel<SchoolBossLevel>();
	GameEngineCore::CreateLevel<CrossTownLevel1>();
	GameEngineCore::CreateLevel<CrossTownLevel2>();
	GameEngineCore::CreateLevel<CrossTownLevel3>();
	GameEngineCore::CreateLevel<TownBossLevel>();
	GameEngineCore::CreateLevel<OceanLevel>();
	GameEngineCore::CreateLevel<OceanBossLevel>();

	GameEngineCore::CreateLevel<Shop_BurgerLevel>();
	GameEngineCore::CreateLevel<Shop_StoreLevel>();
	GameEngineCore::CreateLevel<Shop_GymLevel>();

	ChangeLevel(_StartLevel);
}

void LevelMgr::ChangeLevel(LevelNames _Level)
{
	switch (_Level)
	{
	case LevelNames::Shop_BurgerLevel:
	case LevelNames::Shop_StoreLevel:
	case LevelNames::Shop_GymLevel:
		ShopLevelBase::PrevLevel = NowLevel;
		break;
	default:
		break;
	}

	NowLevel = _Level;
	GameEngineCore::ChangeLevel(EnumToString(_Level));
}




LevelMgr::LevelMgr()
{

}

LevelMgr::~LevelMgr()
{

}
