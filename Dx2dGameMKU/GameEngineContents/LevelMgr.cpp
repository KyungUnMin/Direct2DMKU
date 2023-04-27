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
	"OceanBossLevel"
};


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

	GameEngineCore::ChangeLevel(EnumToString(_StartLevel));
}

void LevelMgr::ChangeLevel(LevelNames _Level)
{
	GameEngineCore::ChangeLevel(EnumToString(_Level));
}




LevelMgr::LevelMgr()
{

}

LevelMgr::~LevelMgr()
{

}
