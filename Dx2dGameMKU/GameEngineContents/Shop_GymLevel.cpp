#include "PrecompileHeader.h"
#include "Shop_GymLevel.h"

#include "RCGEnums.h"

#include "SkillPreviewer.h"

Shop_GymLevel::Shop_GymLevel()
{

}

Shop_GymLevel::~Shop_GymLevel()
{

}



void Shop_GymLevel::Start()
{
	ShopLevelBase::Start();
	ShopLevelBase::SetBgmName("ShopBGM_Gym.mp3");
	CreateBackImage("GymBG.png");

	GameEngineTransform* Trans = nullptr;
	Trans = CreateActor<SkillPreviewer>(UpdateOrder::UI)->GetTransform();
	Trans->SetLocalPosition({ -184.f, -240.f });
}
