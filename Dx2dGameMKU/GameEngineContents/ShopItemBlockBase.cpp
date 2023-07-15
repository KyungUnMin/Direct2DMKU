#include "PrecompileHeader.h"
#include "ShopItemBlockBase.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "DataMgr.h"
#include "RCGEnums.h"


ShopItemBlockBase::ShopItemBlockBase()
{

}

ShopItemBlockBase::~ShopItemBlockBase()
{

}



void ShopItemBlockBase::Init(
	const std::string_view& _CursorTexName,
	const std::string_view& _IconTexName,
	int _Cost, int _Index, std::function<void()> _CallBack)
{
	Index = _Index;
	CursorTexName = _CursorTexName;
	InfoTexName = CursorTexName;
	InfoTexName = InfoTexName.replace(0, 10, "ShopInfo");

	IconRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Item);
	IconRender->SetScaleToTexture(_IconTexName);
	IconRender->Off();

	IconRender->GetTransform()->SetLocalPosition(float4::Left * 220.f);
	GetTransform()->SetLocalRotation(float4::Forward * -10.f);

	Cost = _Cost;
	CallBack = _CallBack;
}




bool ShopItemBlockBase::MoneyCheck()
{
	int PlayerMoney = DataMgr::GetPlayerMoney();
	return (Cost <= PlayerMoney);
}


void ShopItemBlockBase::CallBackExcute()
{
	if (nullptr == CallBack)
	{
		MsgAssert("�ش� ��ų/�������� ���������� ȣ���� �ݹ��� ��ϵ��� �ʾҽ��ϴ�");
		return;
	}

	CallBack();
}
