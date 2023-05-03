#pragma once
#include "ShopItemBlockBase.h"

class ShopItemBlock : public ShopItemBlockBase
{
public:
	ShopItemBlock();
	~ShopItemBlock() override;

	ShopItemBlock(const ShopItemBlock& _Other) = delete;
	ShopItemBlock(ShopItemBlock&& _Other) noexcept = delete;
	ShopItemBlock& operator=(const ShopItemBlock& _Other) = delete;
	ShopItemBlock& operator=(const ShopItemBlock&& _Other) noexcept = delete;

	void Init(const std::string_view& _Name, const std::string_view& _Description,
		const std::string_view& _TextureName, int _Cost, std::function<void()> _CallBack)
	{
		Description = _Description;
		ShopItemBlockBase::Init(_Name, "???", _TextureName, _Cost, _CallBack);
	}

	void HoverIn() override;
	void HoverOut() override;
	void Buy() override;

protected:

private:
	std::string_view Description = "";
};

