#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "LevelMgr.h"

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
	LevelMgr::CreateLevel(LevelNames::Shop_StoreLevel);
}


void RCG_GameCore::GameEnd()
{

}
