#include "PrecompileHeader.h"
#include "ShopItemBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "DataMgr.h"
#include "InventoryMgr.h"

#include "ShopItem_CursorBar.h"
#include "ShopUI_ResultText.h"

ShopItemBlock::ShopItemBlock()
{

}

ShopItemBlock::~ShopItemBlock()
{

}

void ShopItemBlock::HoverIn()
{
	GetIcon()->On();
	ShopItem_CursorBar::ChangeCursorTex(GetCursorTexName());
}

void ShopItemBlock::HoverOut()
{
	GetIcon()->Off();
}


ShopResultType ShopItemBlock::IsAvailable()
{
	if (false == MoneyCheck())
		return ShopResultType::MoneyLack;

	//�κ��丮 ���� üũ
	if(true == InventoryMgr::IsFull())
		return ShopResultType::InvenLack;

	return ShopResultType::BuyOk;
}

void ShopItemBlock::Buy()
{
	if (false == MoneyCheck())
	{
		MsgAssert("���� �����ѵ� �������� �����Ϸ��� �߽��ϴ�");
		return;
	}

	//�κ��丮�� �� á���� Ȯ��
	if (true == InventoryMgr::IsFull())
	{
		MsgAssert("�κ��丮 ������ ���µ� �������� �����Ϸ��� �߽��ϴ�");
		return;
	}

	//��� ����
	DataMgr::MinusPlayerMoney(GetCost());

	//������ �ݹ� ȣ��
	CallBackExcute();
}



void ShopItemBlock::Reset()
{
	ShopItemBlockBase::Reset();

	const size_t NowCursorIndex = ShopItem_CursorBar::GetCurrentIndex();
	const int ThisIndex = GetIndex();

	if (ThisIndex == NowCursorIndex)
	{
		GetIcon()->On();
	}
	else
	{
		GetIcon()->Off();
	}

	if (ThisIndex != NowCursorIndex)
		return;

	ShopItem_CursorBar::ChangeCursorTex(GetCursorTexName());
}