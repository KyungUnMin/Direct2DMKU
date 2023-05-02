#pragma once

struct ShopItemParameter
{
	std::string_view ItemName = "UNKNOWN";
	std::string_view Description = "NO DESCRIPTION";

	//구매하고 난 이후에 처리해야 할 일
	std::function<void(void)> BuyCallBack = nullptr;
	int Cost = INT32_MAX;

	std::string_view ImageName = "";
};

class ShopItemBase
{
public:
	ShopItemBase();
	virtual ~ShopItemBase() = 0;

	ShopItemBase(const ShopItemBase& _Other) = delete;
	ShopItemBase(ShopItemBase&& _Other) noexcept = delete;
	ShopItemBase& operator=(const ShopItemBase& _Other) = delete;
	ShopItemBase& operator=(const ShopItemBase&& _Other) noexcept = delete;

protected:
	
private:

};

