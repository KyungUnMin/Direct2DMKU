#include "PrecompileHeader.h"
#include "SelfRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGEnums.h"
#include "RCGDefine.h"


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

	/*
		참고로 카메라에 등록할 때 Render의 Order를 받아가서
		CameraNum 번째 카메라 Order Group에 넣는다
		즉, 오더가 먼저 지정되고 카메라에 등록된다
	*/
}

void SelfRenderer::SetEnginePipe()
{
	SpriteRenderInit();
}

