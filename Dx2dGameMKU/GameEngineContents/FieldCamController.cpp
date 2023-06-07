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
		MsgAssert("ī�޶� nullptr�� ���� ���Խ��ϴ�");
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
		MsgAssert("��Ʈ�� �� ī�޶� �������� �ʽ��ϴ�. �ʱ�ȭ�� ���־�� �մϴ�\n(������ ������ ���������� �ʾҽ��ϴ� : FieldLevelBase::InitLevelArea ȣ�� �ʿ�)");
		return;
	}

	if (true == Cam->IsFreeCamera())
		return;

	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;


	//ī�޶� ���¿� ���� Update
	Update_CamState(_DeltaTime);
	Update_Zoom(_DeltaTime);
}





