#pragma once
#include "ShopLevelBase.h"

class Shop_GymLevel : public ShopLevelBase
{
public:
	Shop_GymLevel();
	~Shop_GymLevel() override;

	Shop_GymLevel(const Shop_GymLevel& _Other) = delete;
	Shop_GymLevel(Shop_GymLevel&& _Other) noexcept = delete;
	Shop_GymLevel& operator=(const Shop_GymLevel& _Other) = delete;
	Shop_GymLevel& operator=(const Shop_GymLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

