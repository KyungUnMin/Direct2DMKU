#pragma once
#include "ShopItemBase.h"

struct GymItemParameter : public ShopItemParameter
{
	bool IsAcquire = false;
};

class GymItemData : public ShopItemBase
{
public:
	GymItemData();
	~GymItemData() override;

	GymItemData(const GymItemData& _Other) = delete;
	GymItemData(GymItemData&& _Other) noexcept = delete;
	GymItemData& operator=(const GymItemData& _Other) = delete;
	GymItemData& operator=(const GymItemData&& _Other) noexcept = delete;

protected:

private:

};

