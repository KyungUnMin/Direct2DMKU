#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "FieldPlayer.h"


FieldCamController::FieldCamController()
{
	
}

FieldCamController::~FieldCamController()
{

}


void FieldCamController::SetFixedState(const float4& _DestPos)
{
	PrevPos = Cam->GetTransform()->GetLocalForwardVector();
	DestPos = _DestPos;
	Timer = 0.f;

	CurState = CameraCtrlState::MoveToFixed;
}

void FieldCamController::SetShakeState(float _ShakeDuration)
{
	PrevPos = Cam->GetTransform()->GetLocalPosition();
	ShakeDuration = _ShakeDuration;
	Timer = 0.f;
	PrevState = CurState;

	CurState = CameraCtrlState::Shake;
}



void FieldCamController::Update(float _DeltaTime)
{
	if (nullptr == Cam)
	{
		MsgAssert("컨트롤 할 카메라가 존재하지 않습니다. 초기화를 해주어야 합니다");
		return;
	}

	switch (CurState)
	{
	case CameraCtrlState::PlayerTrace:
		Update_Trace(_DeltaTime);
		break;
	case CameraCtrlState::MoveToFixed:
		Update_MoveToFixed(_DeltaTime);
		break;
	case CameraCtrlState::Fixed:
		//외부에서 State값을 바꿔줄때까지 가만히만 있는다
		break;
	case CameraCtrlState::Shake:
		Update_Shake(_DeltaTime);
		break;
	default:
		break;
	}
}


void FieldCamController::Update_Trace(float _DeltaTime)
{
	//카메라가 캐릭터를 따라 다니고 영역 밖으로 나가지 못한다.
	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	if (nullptr == PlayerPtr)
		return;

	float4 PlayerPos = PlayerPtr->GetTransform()->GetWorldPosition();
	GameEngineTransform* CamTransform = Cam->GetTransform();
	float4 CamPos = CamTransform->GetWorldPosition();

	//일단 임시, Lerp가 아니라 가속도 방식으로도 사용 가능
	float4 NextPos = float4::LerpClamp(CamPos, PlayerPos, _DeltaTime);
	NextPos.z = CamPos.z;
	NextPos.w = 1.0f;

	CamTransform->SetWorldPosition(NextPos);
}


void FieldCamController::Update_MoveToFixed(float _DeltaTime)
{
	const float FixMoveDuration = 1.5f;

	Timer += _DeltaTime;
	float Ratio = (Timer / FixMoveDuration);
	
	float4 NowCamPos = float4::LerpClamp(PrevPos, DestPos, Ratio);
	Cam->GetTransform()->SetLocalPosition(NowCamPos);

	if (Ratio < 1.f)
		return;

	CurState = CameraCtrlState::Fixed;
}


void FieldCamController::Update_Shake(float _DeltaTime)
{
	Timer += _DeltaTime;
	GameEngineTransform* CamTrans = Cam->GetTransform();
	if (ShakeDuration < Timer)
	{
		CurState = PrevState;
		CamTrans->SetLocalPosition(PrevPos);
		return;
	}

	const float ShakeRange = 5.f;

	float4 ShakeOffset = float4::Zero;
	ShakeOffset .x = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);
	ShakeOffset .y = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);

	CamTrans->SetLocalPosition(PrevPos + ShakeOffset);
}


