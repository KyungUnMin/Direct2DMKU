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
	const std::string_view& _Name, 
	const std::string_view& _Description, 
	const std::string_view& _TextureName, 
	int _Cost, std::function<void()> _CallBack)
{
	Name = _Name;
	Description = _Description;

	Texture = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Item);
	/*Texture->SetTexture(_TextureName);
	Texture->GetTransform()->SetLocalScale(float4::One * 70.f);*/
	Texture->SetScaleToTexture(_TextureName);
	Texture->Off();

	Texture->GetTransform()->SetLocalPosition(float4::Left * 220.f);
	GetTransform()->SetLocalRotation(float4::Forward * -10.f);

	Cost = _Cost;
	CallBack = _CallBack;
}



void ShopItemBlockBase::ChangeDescription(const std::string_view& _Desc)
{
	Description = _Desc;

	//TODO, 시각적 텍스트를 바꾸는 기능
}



void ShopItemBlockBase::CallBackExcute()
{
	if (nullptr == CallBack)
	{
		MsgAssert("해당 스킬/아이템을 구매했을때 호출할 콜백이 등록되지 않았습니다");
		return;
	}

	CallBack();
}



bool ShopItemBlockBase::MoneyCheck()
{
	int PlayerMoney = DataMgr::GetPlayerMoney();
	return (Cost <= PlayerMoney);
}
