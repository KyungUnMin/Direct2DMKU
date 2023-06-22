#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "FieldPlayer.h"

void FieldCamController::Update_CamState(float _DeltaTime)
{
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
	{
		MsgAssert("카메라가 쫒아갈 플레이어가 존재하지 않습니다");
		return;
	}

	float4 PlayerPos = PlayerPtr->GetTransform()->GetWorldPosition();
	GameEngineTransform* CamTransform = Cam->GetTransform();
	float4 CamPos = CamTransform->GetLocalPosition();

	float TraceRatio = 1.f;
	if (true == PlayerPtr->IsDashing())
	{
		TraceRatio = 5.f;
	}
	float4 NextPos = float4::LerpClamp(CamPos, PlayerPos, TraceRatio * _DeltaTime);

	float4 ScreenSize = GameEngineWindow::GetScreenSize();


	if (
		(NextPos.x - ScreenSize.hx()) < -MapScale.hx()
		|| MapScale.hx() < (NextPos.x + ScreenSize.hx())
		)
	{
		NextPos.x = CamPos.x;
	}

	if (
		(NextPos.y - ScreenSize.hy()) < -MapScale.hy() - TraceYOffset
		|| MapScale.hy() + TraceYOffset < (NextPos.y + ScreenSize.hy())
		)
	{
		NextPos.y = CamPos.y;
	}

	NextPos.z = CamPos.z;
	NextPos.w = 1.0f;

	if (NextPos == CamPos)
		return;

	CamTransform->SetWorldPosition(NextPos);
}


void FieldCamController::Update_MoveToFixed(float _DeltaTime)
{
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


	float4 ShakeOffset = float4::Zero;
	ShakeOffset.x = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);
	ShakeOffset.y = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);

	CamTrans->SetLocalPosition(PrevPos + ShakeOffset);
}
