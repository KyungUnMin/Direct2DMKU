#include "PrecompileHeader.h"
#include "Shop_GymLevel.h"

Shop_GymLevel::Shop_GymLevel()
{

}

Shop_GymLevel::~Shop_GymLevel()
{

}

void Shop_GymLevel::Start()
{
	ShopLevelBase::Start();
	CreateBackImage("GymBG.png");
}
