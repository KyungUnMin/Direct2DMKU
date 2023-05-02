#include "PrecompileHeader.h"
#include "ShopItem_CursorBar.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "KeyMgr.h"

const std::string_view ShopItem_CursorBar::BarRenderName = "ShopUI_SelectionBar.png";
const float4 ShopItem_CursorBar::BarRenderScale = float4{ 610.f, 255.f } * 0.7f;
const float4 ShopItem_CursorBar::BarFirstPos = float4{ 370.f, 30.f };
const float4 ShopItem_CursorBar::BarLastPos = float4{ 320.f, -200.f };

ShopItem_CursorBar::ShopItem_CursorBar()
{

}

ShopItem_CursorBar::~ShopItem_CursorBar()
{

}

void ShopItem_CursorBar::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> BarRender = CreateComponent<GameEngineSpriteRenderer>();
	BarRender->SetTexture(BarRenderName);
	BarRender->GetTransform()->SetLocalScale(BarRenderScale);

	GetTransform()->SetLocalPosition(BarFirstPos);
}



void ShopItem_CursorBar::Update(float _DeltaTime)
{
	const size_t MaxCursor = 3;
	bool IsPosChanged = false;
	if (true == KeyMgr::IsDown(KeyNames::DownArrow) && (CurrentIndex < MaxCursor))
	{
		++CurrentIndex;
		IsPosChanged = true;
	}

	if (true == KeyMgr::IsDown(KeyNames::UpArrow) && (0 < CurrentIndex))
	{
		--CurrentIndex;
		IsPosChanged = true;
	}

	if (false == IsPosChanged)
		return;

	const float Ratio = static_cast<float>(CurrentIndex) / static_cast<float>(MaxCursor);
	float4 NextPos = float4::LerpClamp(BarFirstPos, BarLastPos, Ratio);
	GetTransform()->SetLocalPosition(NextPos);
}
