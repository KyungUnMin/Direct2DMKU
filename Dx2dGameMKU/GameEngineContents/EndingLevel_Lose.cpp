#include "PrecompileHeader.h"
#include "EndingLevel_Lose.h"

#include "SoundMgr.h"
#include "EndingLoseActor.h"

EndingLevel_Lose::EndingLevel_Lose()
{

}

EndingLevel_Lose::~EndingLevel_Lose()
{

}

void EndingLevel_Lose::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	

}

void EndingLevel_Lose::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();

	SoundMgr::ChangeBGM("EndingLose.mp3");
	CreateActor<EndingLoseActor>();
}


//void EndingLevel_Lose::Update(float _DeltaTime)
//{
//}
