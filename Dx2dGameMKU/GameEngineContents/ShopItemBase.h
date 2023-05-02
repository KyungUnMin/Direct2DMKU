#pragma once

/*
	�̷����� Ŭ������ ���� �ʿ䵵 ���� �ʳ�?
	�� ���Ͽ��ٰ� ����� ��� ���� �����
*/


struct ShopItemParameter
{
	std::string_view ItemName = "UNKNOWN";
	std::string_view Description = "NO DESCRIPTION";

	//�����ϰ� �� ���Ŀ� ó���ؾ� �� ��
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

