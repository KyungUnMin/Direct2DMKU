#include "PrecompileHeader.h"
#include "Shop_StoreLevel.h"

Shop_StoreLevel::Shop_StoreLevel()
{

}

Shop_StoreLevel::~Shop_StoreLevel()
{

}

void Shop_StoreLevel::Start()
{
	ShopLevelBase::Start();
	SettingBackImage("StoreBG.png");
}
