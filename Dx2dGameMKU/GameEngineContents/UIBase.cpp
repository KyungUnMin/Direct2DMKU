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
	std::shared_ptr<GameEngineCamera> CamPtr = GetLevel()->GetMainCamera();
	GetTransform()->SetParent(CamPtr->GetTransform());
	GetTransform()->AddLocalPosition(float4::Forward * 10.f);

	/*GetTransform()->SetWorldPosition(CamPtr->GetTransform()->GetWorldPosition());
	GetTransform()->AddWorldPosition(float4::Forward * 10.f);*/
}
