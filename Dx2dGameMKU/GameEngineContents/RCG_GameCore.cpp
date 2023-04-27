#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "OpeningLevel.h"
#include "SchoolEntryLevel.h"
#include "SchoolBossLevel.h"
#include "CrossTownLevel1.h"
#include "CrossTownLevel2.h"
#include "CrossTownLevel3.h"
#include "TownBossLevel.h"
#include "OceanLevel.h"
#include "OceanBossLevel.h"

RCG_GameCore::RCG_GameCore()
{
}

RCG_GameCore::~RCG_GameCore()
{

}

void RCG_GameCore::GameStart()
{
	bool* DEBUGLEAK = new bool;

	ContentsResourceInit();

	KeyMgr::CreateKey();

	GameEngineCore::CreateLevel<OpeningLevel>();
	GameEngineCore::CreateLevel<SchoolEntryLevel>();
	GameEngineCore::CreateLevel<SchoolBossLevel>();
	GameEngineCore::CreateLevel<CrossTownLevel1>();
	GameEngineCore::CreateLevel<CrossTownLevel2>();
	GameEngineCore::CreateLevel<CrossTownLevel3>();
	GameEngineCore::CreateLevel<TownBossLevel>();
	GameEngineCore::CreateLevel<OceanLevel>();
	GameEngineCore::CreateLevel<OceanBossLevel>();

	GameEngineCore::ChangeLevel("SchoolEntryLevel");
}


void RCG_GameCore::GameEnd()
{

}
