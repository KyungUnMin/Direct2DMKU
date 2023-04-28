#pragma once
#include "ShopLevelBase.h"

class Shop_BurgerLevel : public ShopLevelBase
{
public:
	Shop_BurgerLevel();
	~Shop_BurgerLevel() override;

	Shop_BurgerLevel(const Shop_BurgerLevel& _Other) = delete;
	Shop_BurgerLevel(Shop_BurgerLevel&& _Other) noexcept = delete;
	Shop_BurgerLevel& operator=(const Shop_BurgerLevel& _Other) = delete;
	Shop_BurgerLevel& operator=(const Shop_BurgerLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

