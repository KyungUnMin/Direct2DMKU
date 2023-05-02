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
		MsgAssert("FreeCamMoveController의 초기화함수(Init)를 호출해주지 않았습니다");
		return;
	}

	bool IsFreeCamera = CamPtr->IsFreeCamera();

	//프리카메라가 켜진 순간
	if (false == IsPrevFreeCam &&  true == IsFreeCamera)
	{
		PlayerOriginPos = PlayerRenderTrans->GetLocalPosition();
	}

	//프리카메라가 꺼진 순간
	if (true == IsPrevFreeCam && false == IsFreeCamera)
	{
		PlayerRenderTrans->SetLocalPosition(PlayerOriginPos);
	}

	//프리카메라 모드일때
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
