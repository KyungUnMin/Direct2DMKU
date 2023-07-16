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

	void Init(
		const std::string_view& _CursorTexName,
		const std::string_view& _IconTexName, 
		int _Cost, int _Index, std::function<void()> _CallBack)
	{
		ShopItemBlockBase::Init(_CursorTexName, _IconTexName, _Cost, _Index, _CallBack);
	}

	void HoverIn() override;
	void HoverOut() override;

	ShopResultType IsAvailable() override;
	void Buy() override;
	void Reset() override;

protected:

private:
	std::string_view Description = "";
};

