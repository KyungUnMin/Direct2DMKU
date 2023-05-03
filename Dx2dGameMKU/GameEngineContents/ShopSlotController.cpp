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
		MsgAssert("���� ���� ��Ʈ�ѷ��� ���� ���������� ������ �� �ֽ��ϴ�");
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
		"�� ����",
		"ü���� 30% ȸ����Ų��",
		"ShopUI_SingleBurger.png", 2100,
		[]()
	{
		DataMgr::PlusPlayerHP(30);
	});

	ItemBlocks[1] = CreateItemBlock
	(
		"���� �� ����",
		"ü���� 60% ȸ����Ų��",
		"ShopUI_DoubleBurger.png", 2400,
		[]()
	{
		DataMgr::PlusPlayerHP(60);
	});

	ItemBlocks[2] = CreateItemBlock
	(
		"�� ����Ƣ��",
		"ü���� 10% ȸ����Ų��",
		"ShopUI_FriedPotato.png", 1500,
		[]()
	{
		DataMgr::PlusPlayerHP(10);
	});

	ItemBlocks[3] = CreateItemBlock
	(
		"�� ����ũ",
		"ü���� 20% ȸ����Ų��",
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
		"���� ű",0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[1] = CreateSkillBlock
	(
		"���� ű", 0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[2] = CreateSkillBlock
	(
		"���� ű", 0, 15000,
		[]()
	{
		//TODO
	});

	ItemBlocks[3] = CreateSkillBlock
	(
		"���� ű", 0, 15000,
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

	//Ŀ���� �����������
	if (NowCursorIdx == PrevCursorIndex)
		return;


	//����ó��
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

