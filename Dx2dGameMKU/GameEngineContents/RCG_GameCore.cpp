#include "PrecompileHeader.h"
#include "RCG_GameCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include "RCGLevel_Intro.h"

RCG_GameCore::RCG_GameCore()
{

}

RCG_GameCore::~RCG_GameCore()
{

}

void RCG_GameCore::GameStart()
{


	GameEngineCore::CreateLevel<RCGLevel_Intro>();

	GameEngineCore::ChangeLevel("RCGLevel_Intro");
}

void RCG_GameCore::GameEnd()
{

}
