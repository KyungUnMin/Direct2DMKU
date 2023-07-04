#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "LevelMgr.h"
#include "SoundMgr.h"
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

	KeyMgr::CreateKey();
	SoundMgr::Init();
	LevelMgr::CreateLevel(LevelNames::OceanLevel);
}


void RCG_GameCore::GameEnd()
{

}
