#include "PrecompileHeader.h"
#include "FreeCamMoveController.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "FieldLevelBase.h"
#include "FieldPlayer.h"

FreeCamMoveController::FreeCamMoveController()
{

}

FreeCamMoveController::~FreeCamMoveController()
{

}


void FreeCamMoveController::Init(std::shared_ptr<GameEngineCamera> _Cam)
{
	CamPtr = _Cam;
	PlayerRenderTrans = FieldPlayer::GetPtr()->GetRenderer()->GetTransform();
}

void FreeCamMoveController::Update(float _DeltaTime)
{
	if (nullptr == CamPtr)
	{
		MsgAssert("FreeCamMoveController�� �ʱ�ȭ�Լ�(Init)�� ȣ�������� �ʾҽ��ϴ�");
		return;
	}

	bool IsFreeCamera = CamPtr->IsFreeCamera();

	//����ī�޶� ���� ����
	if (false == IsPrevFreeCam &&  true == IsFreeCamera)
	{
		PlayerOriginPos = PlayerRenderTrans->GetLocalPosition();
	}

	//����ī�޶� ���� ����
	if (true == IsPrevFreeCam && false == IsFreeCamera)
	{
		PlayerRenderTrans->SetLocalPosition(PlayerOriginPos);
	}

	//����ī�޶� ����϶�
	if (true == IsFreeCamera)
	{
		Update_FreeCam(_DeltaTime);
	}

	IsPrevFreeCam = IsFreeCamera;
}

void FreeCamMoveController::Update_FreeCam(float _DeltaTime)
{
	const float PlayerJumpAcc = 500.f;
	const float GravityAcc = 500.f;

	//TODO
}
