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
	/*GameEngineTransform* ThisTransform = GetTransform();

	ThisTransform->SetWorldPosition(CamPtr->GetWorldPosition() + float4::Forward);
	ThisTransform->SetParent(CamPtr);*/

	//ThisTransform->SetWorldPosition(CamPtr->GetWorldPosition() + float4::Forward);
}

void UIBase::Update(float _DeltaTime)
{
	float4 CamPos = CamTrans->GetWorldPosition();
	/*if ((PrevCamPos - CamPos).Size() < 1.f)
		return;*/

	GameEngineTransform* ThisTransform = GetTransform();
	ThisTransform->SetWorldPosition(CamPos + float4::Forward);
	PrevCamPos = CamPos;
}
