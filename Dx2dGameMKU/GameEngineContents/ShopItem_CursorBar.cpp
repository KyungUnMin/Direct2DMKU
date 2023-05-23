#include "PrecompileHeader.h"
#include "ShopItem_CursorBar.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"

#include "Shop_GymLevel.h"
#include "ShopSlotController.h"

const std::string_view ShopItem_CursorBar::BarRenderName = "ShopUI_SelectionBar.png";
const std::string_view ShopItem_CursorBar::ConfirmRenderName = "ShopUI_ConfirmBox.png";

const float4 ShopItem_CursorBar::ConfirmRenderScale = float4{ 200.f, 140.f } *0.7f;
const float4 ShopItem_CursorBar::BarRenderScale = float4{ 610.f, 255.f } * 0.7f;

const float4 ShopItem_CursorBar::ShopBarFirstPos = float4{ 370.f, 30.f };
const float4 ShopItem_CursorBar::ShopBarLastPos = float4{ 320.f, -200.f };

const float4 ShopItem_CursorBar::GymBarFirstPos = float4{ 350.f, 70.f };
const float4 ShopItem_CursorBar::GymBarLastPos = float4{ 300.f, -180.f };

const float4 ShopItem_CursorBar::ConfirmInnerOffset = { -100.f, 25.f, 0.f };
const float4 ShopItem_CursorBar::ConfirmOutOffset = { -280.f, 50.f, 0.f };

size_t ShopItem_CursorBar::CurrentIndex = 0;


ShopItem_CursorBar::ShopItem_CursorBar()
{

}

ShopItem_CursorBar::~ShopItem_CursorBar()
{

}


void ShopItem_CursorBar::Start()
{
	//구매 확인 의사를 묻는 박스
	std::shared_ptr<GameEngineUIRenderer> ConfirmBox = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	ConfirmBox->SetTexture(ConfirmRenderName);
	ConfirmBoxTrans = ConfirmBox->GetTransform();
	ConfirmBoxTrans->SetLocalScale(ConfirmRenderScale);
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);

	//아이템을 선택할 수 있는 박스
	std::shared_ptr<GameEngineUIRenderer> BarRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	BarRender->SetTexture(BarRenderName);
	BarRender->GetTransform()->SetLocalScale(BarRenderScale);

	//현제 레벨이 체육관인 경우
	if (nullptr != dynamic_cast<Shop_GymLevel*>(GetLevel()))
	{
		BarFirstPos = GymBarFirstPos;
		BarLastPos = GymBarLastPos;
	}

	GetTransform()->SetLocalPosition(BarFirstPos);

	MaxCursor = ShopSlotController::MaxSlot;
}



void ShopItem_CursorBar::Update(float _DeltaTime)
{
	Update_CursorMove();
	Update_ComfirmMove(_DeltaTime);
}



void ShopItem_CursorBar::Update_CursorMove()
{
	if (true == IsConfirmation)
		return;

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
	{
		//효과음
		return;
	}

	const float Ratio = static_cast<float>(CurrentIndex) / static_cast<float>(MaxCursor);
	float4 NextPos = float4::LerpClamp(BarFirstPos, BarLastPos, Ratio);
	GetTransform()->SetLocalPosition(NextPos);
	//효과음
}

void ShopItem_CursorBar::Update_ComfirmMove(float _DeltaTime)
{
	if (
		true == KeyMgr::IsDown(KeyNames::Z) ||
		true == KeyMgr::IsDown(KeyNames::X)
		)
	{
		IsConfirmation = !IsConfirmation;
		ConfirmTime = 0.f;
	}

	const float Duration = 0.2f;
	ConfirmTime += _DeltaTime;

	float Ratio = (ConfirmTime / Duration);
	if (1.1f < Ratio)
		return;

	float4 NextOffset = float4::Zero;
	if (true == IsConfirmation)
	{
		NextOffset = float4::LerpClamp(ConfirmInnerOffset, ConfirmOutOffset, Ratio);
	}
	else
	{
		NextOffset = float4::LerpClamp(ConfirmOutOffset, ConfirmInnerOffset, Ratio);
	}

	if (NextOffset == ConfirmBoxTrans->GetLocalPosition())
		return;

	ConfirmBoxTrans->SetLocalPosition(NextOffset);
}



void ShopItem_CursorBar::Reset()
{
	CurrentIndex = 0;

	ConfirmTime = FLT_MAX;
	IsConfirmation = false;
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);
}
