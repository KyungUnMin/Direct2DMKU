#pragma once

/*
	일단 텍스트 기능이 나오면 그때 상속/추상클래스로 만들자
	나중에 생각하자
*/

class ShopItemBase
{
public:
	ShopItemBase();
	~ShopItemBase();

	ShopItemBase(const ShopItemBase& _Other) = delete;
	ShopItemBase(ShopItemBase&& _Other) noexcept = delete;
	ShopItemBase& operator=(const ShopItemBase& _Other) = delete;
	ShopItemBase& operator=(const ShopItemBase&& _Other) noexcept = delete;

protected:
	inline void ChangeDescription(const std::string_view& _DescStr)
	{
		Description = _DescStr;
	}



private:
	std::string_view ItemName = "UNKNOWN";
	std::string_view Description = "NO DESCRIPTION";

	//이 아이템/스킬을 구매하기 위한 조건
	std::function<bool(void)> Qualification = nullptr;

	//구매하고 난 이후에 처리해야 할 일
	std::function<void(void)> BuyCallBack = nullptr;

	int Cost = INT32_MAX;
};

