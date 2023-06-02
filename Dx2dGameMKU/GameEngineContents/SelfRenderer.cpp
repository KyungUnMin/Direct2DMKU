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

	//ī�޶� ���ٸ� �����
	if (nullptr == Level->GetCamera(CameraNum))
	{
		Level->CreateCamera(CameraNum, CameraType::Orthogonal);
	}

	//ī�޶� ���
	GameEngineRenderer::PushCameraRender(CameraNum);
}
