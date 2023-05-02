#pragma once
#include "ShopItemBase.h"

class ShopItemData : public ShopItemBase
{
public:
	ShopItemData();
	~ShopItemData();

	ShopItemData(const ShopItemData& _Other) = delete;
	ShopItemData(ShopItemData&& _Other) noexcept = delete;
	ShopItemData& operator=(const ShopItemData& _Other) = delete;
	ShopItemData& operator=(const ShopItemData&& _Other) noexcept = delete;

	inline void Init(const ShopItemParameter& _Data)
	{
		ItemData = _Data;
	}

	inline const std::string_view& GetImageName() const
	{
		return ItemData.ImageName;
	}

protected:

private:
	ShopItemParameter ItemData;
};

