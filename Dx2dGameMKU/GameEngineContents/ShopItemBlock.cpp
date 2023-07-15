#include "PrecompileHeader.h"
#include "ShopItemBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "DataMgr.h"

#include "ShopItem_CursorBar.h"

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


void ShopItemBlock::Buy()
{
	if (false == MoneyCheck())
	{
		MsgAssert("���� �����ѵ� �������� �����Ϸ��� �߽��ϴ�");
		return;
	}

	//�κ��丮�� �� á���� Ȯ��
	//MsgAssert("�κ��丮 ������ ���µ� �������� �����Ϸ��� �߽��ϴ�");



	//������ �ݹ� ȣ��
	CallBackExcute();
}
