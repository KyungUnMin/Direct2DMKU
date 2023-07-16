#include "PrecompileHeader.h"
#include "ShopItemBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

#include "DataMgr.h"

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

	//인벤토리 공간 체크


	return ShopResultType::BuyOk;
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