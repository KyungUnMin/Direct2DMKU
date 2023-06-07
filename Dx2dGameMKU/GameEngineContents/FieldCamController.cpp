#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "RCG_GameCore.h"



FieldCamController::FieldCamController()
{
	
}

FieldCamController::~FieldCamController()
{

}


void FieldCamController::Init(std::shared_ptr<GameEngineCamera> _Cam, const float4& _MapScale)
{
	if (nullptr == _Cam)
	{
		MsgAssert("카메라에 nullptr인 값이 들어왔습니다");
		return;
	}

	Cam = _Cam;
	MapScale = _MapScale;
	//PrevZoomPercent = Cam->GetZoomRatio();
	SetZoom();
}



void FieldCamController::SetFixedState(const float4& _DestPos)
{
	PrevPos = Cam->GetTransform()->GetLocalForwardVector();
	DestPos = _DestPos;
	Timer = 0.f;

	CurState = CameraCtrlState::MoveToFixed;
}

void FieldCamController::SetShakeState(float _ShakeDuration, float _ShakeRange /*= 5.f*/)
{
	PrevPos = Cam->GetTransform()->GetLocalPosition();
	ShakeDuration = _ShakeDuration;
	ShakeRange = _ShakeRange;
	Timer = 0.f;
	PrevState = CurState;

	CurState = CameraCtrlState::Shake;
}





void FieldCamController::Update(float _DeltaTime)
{
	if (nullptr == Cam)
	{
		MsgAssert("컨트롤 할 카메라가 존재하지 않습니다. 초기화를 해주어야 합니다\n(레벨의 영역을 설정해주지 않았습니다 : FieldLevelBase::InitLevelArea 호출 필요)");
		return;
	}

	if (true == Cam->IsFreeCamera())
		return;

	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;


	//카메라 상태에 따른 Update
	Update_CamState(_DeltaTime);
	Update_Zoom(_DeltaTime);
}





