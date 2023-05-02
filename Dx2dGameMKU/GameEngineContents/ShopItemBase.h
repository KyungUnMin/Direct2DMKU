#pragma once

/*
	�ϴ� �ؽ�Ʈ ����� ������ �׶� ���/�߻�Ŭ������ ������
	���߿� ��������
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

	//�� ������/��ų�� �����ϱ� ���� ����
	std::function<bool(void)> Qualification = nullptr;

	//�����ϰ� �� ���Ŀ� ó���ؾ� �� ��
	std::function<void(void)> BuyCallBack = nullptr;

	int Cost = INT32_MAX;
};

