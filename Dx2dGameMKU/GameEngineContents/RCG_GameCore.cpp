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
#endif

	ContentsResourceInit();
	//GUIManager::Init();

	KeyMgr::CreateKey();

	/*GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::ChangeLevel("TestLevel");*/

	LevelMgr::CreateLevel(LevelNames::SchoolEntryLevel);
}


void RCG_GameCore::GameEnd()
{

}
