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
	//�÷��̾� ���� üũ
	if (DataMgr::GetPlayerLevel() < UnlockLevel)
		return ShopResultType::LevelLack;

	//�ܾ� üũ
	if (false == MoneyCheck())
		return ShopResultType::MoneyLack;
	
	//�̹� ������
	if (true == PrevAquired)
		return ShopResultType::SoldOut;

	return ShopResultType::BuyOk;
}


void ShopSkillBlock::Buy()
{
	if (false == MoneyCheck())
	{
		MsgAssert("���� �����ѵ� �������� �����Ϸ��� �߽��ϴ�");
		return;
	}

	if (true == PrevAquired)
	{
		MsgAssert("������ ������ ��ų�� �ٽ� ������ ���� �����ϴ�");
		return;
	}

	//���� Ȯ�� ������ On
	GetIcon()->On();

	PrevAquired = true;
	DataMgr::MinusPlayerMoney(GetCost());

	//������ �ݹ� ȣ��
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
