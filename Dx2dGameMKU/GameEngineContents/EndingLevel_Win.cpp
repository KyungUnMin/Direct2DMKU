#include "PrecompileHeader.h"
#include "EndingLevel_Win.h"

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


void EndingLevel_Win::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	MsgTextBox("¿ì¿Í ²£´Ù!");
}