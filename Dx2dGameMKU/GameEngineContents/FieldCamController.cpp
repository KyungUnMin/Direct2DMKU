#include "PrecompileHeader.h"
#include "FieldCamController.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FieldPlayer.h"
#include "KeyMgr.h"

FieldCamController::FieldCamController()
{
	
}

FieldCamController::~FieldCamController()
{

}


void FieldCamController::Init(std::shared_ptr<GameEngineCamera> _Cam, const float4& _MapScale)
{
	Cam = _Cam;
	MapScale = _MapScale;

	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	if (nullptr == PlayerPtr)
	{
		MsgAssert("�÷��̾ ���� �������� �ʾ� �÷��̾��� �������� ������ �� �����ϴ�");
		return;
	}

	PlayerRender = PlayerPtr->GetRenderer();
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
		MsgAssert("��Ʈ�� �� ī�޶� �������� �ʽ��ϴ�. �ʱ�ȭ�� ���־�� �մϴ�\n(������ ������ ���������� �ʾҽ��ϴ� : FieldLevelBase::InitLevelArea ȣ�� �ʿ�)");
		return;
	}

	IsFreeCamMode = Cam->IsFreeCamera();

	//����ī�޶� ���� ����
	if (false == PrevCamMode && true == IsFreeCamMode)
	{
		PlayerOriginOffset = PlayerRender->GetTransform()->GetLocalPosition();
		PlayerGravity = 0.f;
	}

	//����ī�޶� ���� ����
	else if (true == PrevCamMode && false == IsFreeCamMode)
	{
		PlayerRender->GetTransform()->SetLocalPosition(PlayerOriginOffset);
	}

	//����ī�޶� ����϶�
	if (true == IsFreeCamMode)
	{
		Update_FreeCam(_DeltaTime);
	}

	//�Ϲ����� ī�޶� ��� �϶�
	else
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
			//�ܺο��� State���� �ٲ��ٶ����� �������� �ִ´�
			break;
		case CameraCtrlState::Shake:
			Update_Shake(_DeltaTime);
			break;
		default:
			break;
		}
	}

	PrevCamMode = IsFreeCamMode;
}


void FieldCamController::Update_Trace(float _DeltaTime)
{
	//ī�޶� ĳ���͸� ���� �ٴϰ� ���� ������ ������ ���Ѵ�.
	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	if (nullptr == PlayerPtr)
	{
		MsgAssert("ī�޶� �i�ư� �÷��̾ �������� �ʽ��ϴ�");
		return;
	}

	float4 PlayerPos = PlayerPtr->GetTransform()->GetWorldPosition();
	GameEngineTransform* CamTransform = Cam->GetTransform();
	float4 CamPos = CamTransform->GetLocalPosition();

	/*float OriginCamZ = CamPos.z;
	PlayerPos.z = 0.f;
	CamPos.z = 0.f;

	const float StopDistance = 10.f;
	float4 Dir = (PlayerPos - CamPos);
	if (Dir.Size() < StopDistance)
		return;

	Dir.Normalize();
	const float MoveSpeed = 200.f;
	float4 NextPos = CamPos + (Dir * MoveSpeed * _DeltaTime);

	if (NextPos.x < -MapScale.hx() || MapScale.hx() < NextPos.x)
		return;

	if (NextPos.y < -MapScale.hy() || MapScale.hy() < NextPos.y)
		return;

	NextPos.z = OriginCamZ;
	CamTransform->SetLocalPosition(NextPos);*/

	float4 NextPos = float4::LerpClamp(CamPos, PlayerPos, _DeltaTime);
	
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	if (
		(NextPos.x - ScreenSize.hx()) < -MapScale.hx()
		|| MapScale.hx() < (NextPos.x + ScreenSize.hx())
		)
	{
		NextPos.x = CamPos.x;
	}

	if (
		(NextPos.y - ScreenSize.hy()) < -MapScale.hy()
		|| MapScale.hy() < (NextPos.y + ScreenSize.hy())
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




void FieldCamController::Update_FreeCam(float _DeltaTime)
{
	const float PlayerJumpAcc = 500.f;
	const float GravityAcc = 500.f;

	if (true == KeyMgr::IsDown(KeyNames::Space))
	{
		PlayerGravity += PlayerJumpAcc;
	}

	PlayerGravity -= GravityAcc * _DeltaTime;
	if (PlayerGravity < 0.f)
	{
		PlayerGravity = 0.f;
	}

	PlayerRender->GetTransform()->SetLocalPosition(PlayerOriginOffset + (float4::Up * PlayerGravity * _DeltaTime));
}

