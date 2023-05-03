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
		"텍 버거",
		"체력을 30% 회복시킨다",
		"ShopUI_SingleBurger.png", 2100,
		[]()
	{
		DataMgr::PlusPlayerHP(30);
	});

	ItemBlocks[1] = CreateItemBlock
	(
		"더블 텍 버거",
		"체력을 60% 회복시킨다",
		"ShopUI_DoubleBurger.png", 2400,
		[]()
	{
		DataMgr::PlusPlayerHP(60);
	});

	ItemBlocks[2] = CreateItemBlock
	(
		"텍 감자튀김",
		"체력을 10% 회복시킨다",
		"ShopUI_FriedPotato.png", 1500,
		[]()
	{
		DataMgr::PlusPlayerHP(10);
	});

	ItemBlocks[3] = CreateItemBlock
	(
		"텍 쉐이크",
		"체력을 20% 회복시킨다",
		"ShopUI_Shake.png", 1800,
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
		"마하 킥",0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[1] = CreateSkillBlock
	(
		"마하 킥", 0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[2] = CreateSkillBlock
	(
		"마하 킥", 0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[3] = CreateSkillBlock
	(
		"마하 킥", 0, 15000,
		[]()
	{
		//TODO
	});


}

void ShopSlotController::Init_Store()
{

}




std::shared_ptr<ShopItemBlockBase> ShopSlotController::CreateItemBlock(
	const std::string_view& _Name,
	const std::string_view& _Description,
	const std::string_view& _TextureName,
	int _Cost, std::function<void()> _CallBack)
{
	std::shared_ptr<ShopItemBlock> Block = GetLevel()->CreateActor<ShopItemBlock>(static_cast<int>(UpdateOrder::UI));
	Block->Init(_Name, _Description, _TextureName, _Cost, _CallBack);
	return Block;
}



std::shared_ptr<ShopItemBlockBase> ShopSlotController::CreateSkillBlock(
	const std::string_view& _Name, int _UnlockLevel,
	int _Cost, std::function<void()> _CallBack)
{
	std::shared_ptr<ShopSkillBlock> Block = GetLevel()->CreateActor<ShopSkillBlock>(static_cast<int>(UpdateOrder::UI));
	Block->Init(_Name,_UnlockLevel,_Cost, _CallBack);
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

