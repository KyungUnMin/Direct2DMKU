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
#ifdef _DEBUG
	bool* DEBUGLEAK = new bool;
#endif

	ContentsResourceInit();

	KeyMgr::CreateKey();
	LevelMgr::CreateLevel(LevelNames::SchoolEntryLevel);
}


void RCG_GameCore::GameEnd()
{

}
