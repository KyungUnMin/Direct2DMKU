#include "PrecompileHeader.h"
#include "ShopSkillBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "ShopItem_CursorBar.h"

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

	//�κ��丮�� �� á���� Ȯ��
	//MsgAssert("�κ��丮 ������ ���µ� �������� �����Ϸ��� �߽��ϴ�");

	//���� Ȯ�� ������ On
	GetIcon()->On();

	PrevAquired = true;

	//������ �ݹ� ȣ��
	CallBackExcute();
}
