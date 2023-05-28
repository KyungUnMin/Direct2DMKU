#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineCore/GameEngineCamera.h>

const float FieldCamController::ZoomOrigin = 1.0f;

void FieldCamController::SetZoom(float _Per, float _Duration /*= 0.5f*/)
{
	ZoomTimer = 0.0f;

	DestZoomPercent = _Per;
	ZoomMoveDuration = _Duration;
	PrevZoomPercent = Cam->GetZoomRatio();
}

void FieldCamController::SetZoom(float _Per)
{
	Cam->SetZoomRatio(_Per);
}

void FieldCamController::Update_Zoom(float _DeltaTime)
{
	ZoomTimer += _DeltaTime;
	if (ZoomMoveDuration < ZoomTimer)
	{
		Cam->SetZoomRatio(DestZoomPercent);
		return;
	}

	float Ratio = (ZoomTimer / ZoomMoveDuration);
	float NowZoomPer = (DestZoomPercent * Ratio) + (PrevZoomPercent * (1.f - Ratio));
	Cam->SetZoomRatio(NowZoomPer);
}