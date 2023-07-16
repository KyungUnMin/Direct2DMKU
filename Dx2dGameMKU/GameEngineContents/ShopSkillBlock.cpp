#include "PrecompileHeader.h"
#include "ShopSkillBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "DataMgr.h"

#include "ShopItem_CursorBar.h"
#include "ShopUI_ResultText.h"

ShopSkillBlock::ShopSkillBlock()
{

}

ShopSkillBlock::~ShopSkillBlock()
{

}



void ShopSkillBlock::HoverIn()
{
	ShopItem_CursorBar::ChangeCursorTex(GetCursorTexName());
}




ShopResultType ShopSkillBlock::IsAvailable()
{
	//플레이어 레벨 체크
	if (DataMgr::GetPlayerLevel() < UnlockLevel)
		return ShopResultType::LevelLack;

	//잔액 체크
	if (false == MoneyCheck())
		return ShopResultType::MoneyLack;
	
	//이미 구매함
	if (true == PrevAquired)
		return ShopResultType::SoldOut;

	return ShopResultType::BuyOk;
}


void ShopSkillBlock::Buy()
{
	if (false == MoneyCheck())
	{
		MsgAssert("돈이 부족한데 아이템을 구매하려고 했습니다");
		return;
	}

	if (true == PrevAquired)
	{
		MsgAssert("이전에 구입한 스킬을 다시 구매할 수는 없습니다");
		return;
	}

	//구매 확인 렌더러 On
	GetIcon()->On();

	PrevAquired = true;
	DataMgr::MinusPlayerMoney(GetCost());

	//구매후 콜백 호출
	CallBackExcute();
}

void ShopSkillBlock::Reset()
{
	ShopItemBlockBase::Reset();

	const size_t NowCursorIndex = ShopItem_CursorBar::GetCurrentIndex();
	const int ThisIndex = GetIndex();

	if (ThisIndex != NowCursorIndex)
		return;
	
	ShopItem_CursorBar::ChangeCursorTex(GetCursorTexName());
}
