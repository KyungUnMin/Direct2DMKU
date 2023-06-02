#include "PrecompileHeader.h"
#include "SelfRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGEnums.h"

SelfRenderer::SelfRenderer()
{

}

SelfRenderer::~SelfRenderer()
{

}


void SelfRenderer::SetCamera(RCG_CamNumType _CamType)
{
	GameEngineLevel* Level = GetLevel();
	int CameraNum = static_cast<int>(_CamType);

	//카메라가 없다면 만든다
	if (nullptr == Level->GetCamera(CameraNum))
	{
		Level->CreateCamera(CameraNum, CameraType::Orthogonal);
	}

	//카메라에 등록
	GameEngineRenderer::PushCameraRender(CameraNum);
}
