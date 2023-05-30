#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "LevelMgr.h"
#include "GUIManager.h"

#include "TestLevel.h"

GameState RCG_GameCore::CurState = GameState::OnField;

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
	//GUIManager::Init();
#endif

	ContentsResourceInit();

	KeyMgr::CreateKey();
	LevelMgr::CreateLevel(LevelNames::CrossTownLevel1);
}


void RCG_GameCore::GameEnd()
{

}
