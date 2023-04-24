#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>

#include "KeyMgr.h"
#include "OpeningLevel.h"

RCG_GameCore::RCG_GameCore()
{

}

RCG_GameCore::~RCG_GameCore()
{

}

void RCG_GameCore::GameStart()
{
	KeyMgr::CreateKey();

	GameEngineCore::CreateLevel<OpeningLevel>();

	GameEngineCore::ChangeLevel("OpeningLevel");
}

void RCG_GameCore::GameEnd()
{

}
