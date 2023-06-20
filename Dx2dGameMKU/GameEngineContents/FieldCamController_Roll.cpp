#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineCore/GameEngineCamera.h>

const float FieldCamController::RollOrigin = 0.f;




void FieldCamController::SetRoll(float _Degree, float _Duration /*= 0.5f*/)
{
	RollTimer = 0.0f;

	DestRollAngle = _Degree;
	RollDuration = _Duration;

	GameEngineTransform* CamTrans = Cam->GetTransform();
	PrevRollAngle = CamTrans->GetLocalRotation().z;
}

void FieldCamController::SetRoll(float _Degree)
{
	GameEngineTransform* CamTrans = Cam->GetTransform();
	CamTrans->SetLocalRotation(float4::Forward * _Degree);
	RollDuration = FLT_MAX;

	DestRollAngle = _Degree;
	PrevRollAngle = _Degree;
}



void FieldCamController::Update_Roll(float _DeltaTime)
{
	GameEngineTransform* CamTrans = Cam->GetTransform();
	const TransformData& DEBUG = CamTrans->GetTransDataRef();

	RollTimer += _DeltaTime;
	if (RollDuration < RollTimer)
	{
		CamTrans->SetLocalRotation(float4::Forward * DestRollAngle);
		return;
	}

	float Ratio = (RollTimer / RollDuration);
	float NowAngle = (DestRollAngle * Ratio) + (PrevRollAngle * (1.f - Ratio));
	CamTrans->SetLocalRotation(float4::Forward * NowAngle);
}