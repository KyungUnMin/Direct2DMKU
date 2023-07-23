#include "PrecompileHeader.h"
#include "Shop_BurgerLevel.h"




Shop_BurgerLevel::Shop_BurgerLevel()
{

}

Shop_BurgerLevel::~Shop_BurgerLevel()
{

}

void Shop_BurgerLevel::Start()
{
	ShopLevelBase::Start();
	ShopLevelBase::SetBgmName("ShopBGM_Bugger.mp3");
	CreateBackImage("BurgerBG.png");
}

