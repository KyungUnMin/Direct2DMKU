#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "LevelMgr.h"
#include "GUIManager.h"

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
	GUIManager::Init();

	KeyMgr::CreateKey();
	LevelMgr::CreateLevel(LevelNames::Shop_GymLevel);
}


void RCG_GameCore::GameEnd()
{

}
