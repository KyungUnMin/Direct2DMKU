#pragma once
#include "ShopLevelBase.h"

class Shop_StoreLevel : public ShopLevelBase
{
public:
	Shop_StoreLevel();
	~Shop_StoreLevel() override;

	Shop_StoreLevel(const Shop_StoreLevel& _Other) = delete;
	Shop_StoreLevel(Shop_StoreLevel&& _Other) noexcept = delete;
	Shop_StoreLevel& operator=(const Shop_StoreLevel& _Other) = delete;
	Shop_StoreLevel& operator=(const Shop_StoreLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

