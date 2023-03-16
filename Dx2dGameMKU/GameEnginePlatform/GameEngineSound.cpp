#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

//시스템 사운드
FMOD::System* SoundSystem = nullptr;

//생성자를 이용한 시스템 사운드 할당
class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		//시스템 사운드 생성
		FMOD::System_Create(&SoundSystem);
		if (nullptr == SoundSystem)
		{
			MsgAssert("사운드 초기화가 제대로 되지 않았습니다");
		}

		//시스템 사운드 초기화
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgAssert("사운드 시스템 이니셜라이즈에 실패했습니다");
		}
	}

	//시스템 사운드 해제
	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject;

void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("사운드 업데이트가 불가능합니다");
		return;
	}

	SoundSystem->update();
}








GameEngineSound::GameEngineSound()
{

}

GameEngineSound::~GameEngineSound()
{

}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{
	if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
	{
		MsgAssert(std::string("사운드 로드에 실패하였습니다.\n경로 : ") + _Path.data());
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert("FMODSound가 nullptr입니다");
	}

	FMOD::Channel* Return;
	SoundSystem->playSound(FMODSound, nullptr, false, &Return);
	return Return;
}
