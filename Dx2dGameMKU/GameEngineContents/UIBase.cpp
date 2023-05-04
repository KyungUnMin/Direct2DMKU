#include "PrecompileHeader.h"
#include "UIBase.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

UIBase::UIBase()
{

}

UIBase::~UIBase()
{

}

void UIBase::Start()
{
	CamTrans = GetLevel()->GetMainCamera()->GetTransform();
}

void UIBase::Update(float _DeltaTime)
{
	float4 CamPos = CamTrans->GetWorldPosition();
	GameEngineTransform* ThisTransform = GetTransform();
	ThisTransform->SetWorldPosition(CamPos + OffsetFromCam);
	PrevCamPos = CamPos;
}
