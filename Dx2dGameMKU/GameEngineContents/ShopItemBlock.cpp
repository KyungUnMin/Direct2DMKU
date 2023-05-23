#include "PrecompileHeader.h"
#include "ShopItemBlock.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "DataMgr.h"

ShopItemBlock::ShopItemBlock()
{

}

ShopItemBlock::~ShopItemBlock()
{

}

void ShopItemBlock::HoverIn()
{
	GetTexture()->On();
}

void ShopItemBlock::HoverOut()
{
	GetTexture()->Off();
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


	ChangeDescription(Description);

	//������ �ݹ� ȣ��
	CallBackExcute();
}
