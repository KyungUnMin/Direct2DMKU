#include "PrecompileHeader.h"
#include "ShopInfo.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"

#include "Shop_BurgerLevel.h"
#include "Shop_GymLevel.h"
#include "Shop_StoreLevel.h"

ShopInfo::ShopInfo()
{

}

ShopInfo::~ShopInfo()
{

}

void ShopInfo::Start()
{
	std::string_view TextureName = "";
	if (nullptr != dynamic_cast<Shop_BurgerLevel*>(GetLevel()))
	{
		TextureName = "ShopUI_BurgerInfo.png";
	}
	else if (nullptr != dynamic_cast<Shop_GymLevel*>(GetLevel()))
	{
		TextureName = "ShopUI_GymInfo.png";
	}
	else if (nullptr != dynamic_cast<Shop_StoreLevel*>(GetLevel()))
	{
		TextureName = "ShopUI_StoreInfo.png";
	}
	else
	{
		MsgAssert("ShopInfo 엑터가 상점이 아닌 레벨에서 생성되었습니다");
		return;
	}

	std::shared_ptr<GameEngineUIRenderer> SpritePtr = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Info);
	SpritePtr->SetTexture(TextureName);

	const float4 RenderScale = float4{ 400.f, 139.f } * 0.7f;
	SpritePtr->GetTransform()->SetLocalScale(RenderScale);
	SpritePtr->GetTransform()->SetLocalPosition(RenderScale.half());

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GetTransform()->SetLocalPosition(-ScreenSize.half() + float4{10.f, 10.f});
}
