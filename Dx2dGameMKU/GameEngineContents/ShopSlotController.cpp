#include "PrecompileHeader.h"
#include "ShopSlotController.h"

#include "RCGEnums.h"
#include "DataMgr.h"

#include "Shop_BurgerLevel.h"
#include "Shop_GymLevel.h"
#include "Shop_StoreLevel.h"

#include "ShopItemBlock.h"
#include "ShopSkillBlock.h"
#include "ShopItem_CursorBar.h"

const size_t ShopSlotController::MaxSlot = 3;

ShopSlotController::ShopSlotController()
{

}

ShopSlotController::~ShopSlotController()
{

}

void ShopSlotController::Start()
{
	GameEngineLevel* Level = GetLevel();
	float4 BeginPos = float4::Zero;
	float4 EndPos = float4::Zero;

	if (nullptr != dynamic_cast<Shop_BurgerLevel*>(Level))
	{
		Init_Burger();
		BeginPos = ShopItem_CursorBar::ShopBarFirstPos;
		EndPos = ShopItem_CursorBar::ShopBarLastPos;
	}
	else if (nullptr != dynamic_cast<Shop_GymLevel*>(Level))
	{
		Init_Gym();
		BeginPos = ShopItem_CursorBar::GymBarFirstPos;
		EndPos = ShopItem_CursorBar::GymBarLastPos;
	}
	else if (nullptr != dynamic_cast<Shop_StoreLevel*>(Level))
	{
		Init_Store();
		BeginPos = ShopItem_CursorBar::ShopBarFirstPos;
		EndPos = ShopItem_CursorBar::ShopBarLastPos;
	}
	else
	{
		MsgAssert("상점 슬롯 컨트롤러는 상점 레벨에서만 생성할 수 있습니다");
		return;
	}

	
	for (size_t i = 0; i < ItemBlocks.size(); ++i)
	{
		float PosRatio = static_cast<float>(i) / static_cast<float>(MaxSlot);
		const float4 Offset = float4::LerpClamp(BeginPos, EndPos, PosRatio);
		ItemBlocks[i]->GetTransform()->SetLocalPosition(Offset);
	}
}






void ShopSlotController::Init_Burger()
{
	ItemBlocks.resize(MaxSlot + 1, nullptr);

	ItemBlocks[0] = CreateItemBlock
	(
		"ShopCursor_SingleTeckBurger.png",
		"ShopUI_SingleBurger.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(30);
	});

	ItemBlocks[1] = CreateItemBlock
	(
		"ShopCursor_DoubleBurger.png",
		"ShopUI_DoubleBurger.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(60);
	});

	ItemBlocks[2] = CreateItemBlock
	(
		"ShopCursor_TeckFried.png",
		"ShopUI_FriedPotato.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(10);
	});

	ItemBlocks[3] = CreateItemBlock
	(
		"ShopCursor_TeckShake.png",
		"ShopUI_Shake.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(20);
	});
}

void ShopSlotController::Init_Gym()
{
	ItemBlocks.resize(MaxSlot + 1, nullptr);

	ItemBlocks[0] = CreateSkillBlock
	(
		"ShopUI_SelectionBar.png",
		9999,9999,
		[]()
	{
		//TODO
	});

	ItemBlocks[1] = CreateSkillBlock
	(
		"ShopUI_SelectionBar.png",
		9999, 9999,
		[]()
	{
		//TODO
	});

	ItemBlocks[2] = CreateSkillBlock
	(
		"ShopUI_SelectionBar.png",
		9999, 9999,
		[]()
	{
		//TODO
	});

	ItemBlocks[3] = CreateSkillBlock
	(
		"ShopUI_SelectionBar.png",
		9999, 9999,
		[]()
	{
		//TODO
	});


}

void ShopSlotController::Init_Store()
{
	ItemBlocks.resize(MaxSlot + 1, nullptr);

	ItemBlocks[0] = CreateItemBlock
	(
		"ShopCursor_Candy.png",
		"ShopUI_Candy.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(30);
	});

	ItemBlocks[1] = CreateItemBlock
	(
		"ShopCursor_CottonCandy.png",
		"ShopUI_CottonCandy.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(60);
	});

	ItemBlocks[2] = CreateItemBlock
	(
		"ShopCursor_GummyYummi.png",
		"ShopUI_GummyYummi.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(10);
	});

	ItemBlocks[3] = CreateItemBlock
	(
		"ShopCursor_MelonMint.png",
		"ShopUI_MelonMint.png", 9999,
		[]()
	{
		DataMgr::PlusPlayerHP(20);
	});
}




std::shared_ptr<ShopItemBlockBase> ShopSlotController::CreateItemBlock(
	const std::string_view& _CursorTexName,
	const std::string_view& _IconTexName,
	int _Cost, std::function<void()> _CallBack)
{
	std::shared_ptr<ShopItemBlock> Block = GetLevel()->CreateActor<ShopItemBlock>(static_cast<int>(UpdateOrder::UI));
	Block->Init(_CursorTexName, _IconTexName, _Cost, _CallBack);
	return Block;
}



std::shared_ptr<ShopItemBlockBase> ShopSlotController::CreateSkillBlock(
	const std::string_view& _CursorTexName,
	int _Cost, int _UnlockLevel,
	std::function<void()> _CallBack)
{
	std::shared_ptr<ShopSkillBlock> Block = GetLevel()->CreateActor<ShopSkillBlock>(static_cast<int>(UpdateOrder::UI));
	Block->Init(_CursorTexName, _Cost, _CallBack, _UnlockLevel);
	return Block;
}


void ShopSlotController::Update(float _DelatTime)
{
	Update_Buy();
	Update_Select();
}

void ShopSlotController::Update_Buy()
{

}

void ShopSlotController::Update_Select()
{
	size_t NowCursorIdx = ShopItem_CursorBar::GetCurrentIndex();

	//커서가 변경됐을때만
	if (NowCursorIdx == PrevCursorIndex)
		return;


	//예외처리
	size_t ArrSize = ItemBlocks.size();
	if (PrevCursorIndex < ArrSize)
	{
		ItemBlocks[PrevCursorIndex]->HoverOut();
	}
	if (NowCursorIdx < ArrSize)
	{
		ItemBlocks[NowCursorIdx]->HoverIn();
	}

	//TODO

	PrevCursorIndex = NowCursorIdx;
}

