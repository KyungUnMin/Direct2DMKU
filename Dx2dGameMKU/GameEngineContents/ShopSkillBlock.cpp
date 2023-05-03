#include "PrecompileHeader.h"
#include "ShopSkillBlock.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

ShopSkillBlock::ShopSkillBlock()
{

}

ShopSkillBlock::~ShopSkillBlock()
{

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
	GetTexture()->On();

	PrevAquired = true;

	//������ �ݹ� ȣ��
	CallBackExcute();
}
