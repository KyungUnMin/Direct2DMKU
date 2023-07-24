#include "PrecompileHeader.h"
#include "RCG_GameCore.h"

#include "KeyMgr.h"
#include "LevelMgr.h"
#include "SoundMgr.h"
#include "GUIManager.h"
#include "SkillMgr.h"
#include "FontMgr.h"

GameState RCG_GameCore::CurState = GameState::OnField;
std::vector<GameEngineFile> RCG_GameCore::FontFiles;

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

	FontMgr::Init();
	ContentsResourceInit();

	KeyMgr::CreateKey();
	SoundMgr::Init();
	SkillMgr::Init();

	LevelMgr::CreateLevel(LevelNames::OpeningLevel);

	//시연회 용
	GameEngineSoundPlayer::CanVolumeChange = false;
}




void RCG_GameCore::GameEnd()
{
	FontMgr::Clear();
}
