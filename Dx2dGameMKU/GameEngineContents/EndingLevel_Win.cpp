#include "PrecompileHeader.h"
#include "EndingLevel_Win.h"

#include "RCGEnums.h"

#include "EndingWinActor.h"
#include "Fader.h"

EndingLevel_Win::EndingLevel_Win()
{

}

EndingLevel_Win::~EndingLevel_Win()
{

}

void EndingLevel_Win::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	

}


void EndingLevel_Win::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Black);
	CreateActor<EndingWinActor>(UpdateOrder::Defalut);
}


void EndingLevel_Win::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	
}