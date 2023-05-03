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
		MsgAssert("돈이 부족한데 아이템을 구매하려고 했습니다");
		return;
	}

	if (true == PrevAquired)
	{
		MsgAssert("이전에 구입한 스킬을 다시 구매할 수는 없습니다");
		return;
	}

	//인벤토리가 꽉 찼는지 확인
	//MsgAssert("인벤토리 공간이 없는데 아이템을 구매하려고 했습니다");

	//구매 확인 렌더러 On
	GetTexture()->On();

	PrevAquired = true;

	//구매후 콜백 호출
	CallBackExcute();
}
