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
		MsgAssert("돈이 부족한데 아이템을 구매하려고 했습니다");
		return;
	}

	//인벤토리가 꽉 찼는지 확인
	//MsgAssert("인벤토리 공간이 없는데 아이템을 구매하려고 했습니다");



	//구매후 콜백 호출
	CallBackExcute();
}
