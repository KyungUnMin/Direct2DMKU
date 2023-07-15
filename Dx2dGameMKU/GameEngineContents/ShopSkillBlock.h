#pragma once
#include "ShopItemBlockBase.h"

class ShopSkillBlock : public ShopItemBlockBase
{
public:
	ShopSkillBlock();
	~ShopSkillBlock() override;

	ShopSkillBlock(const ShopSkillBlock& _Other) = delete;
	ShopSkillBlock(ShopSkillBlock&& _Other) noexcept = delete;
	ShopSkillBlock& operator=(const ShopSkillBlock& _Other) = delete;
	ShopSkillBlock& operator=(const ShopSkillBlock&& _Other) noexcept = delete;

	void Init(
		const std::string_view& _CursorTexName,
		int _Cost, int _UnlockLevel, int _Index,
		std::function<void()> _CallBack)
	{
		static const std::string_view IconTexName = "GymCheckIcon.png";

		UnlockLevel = _UnlockLevel;
		ShopItemBlockBase::Init(_CursorTexName, IconTexName, _Cost, _Index, _CallBack);
	}

	void HoverIn() override;
	void Buy() override;

protected:

private:
	int UnlockLevel = INT32_MAX;
	bool PrevAquired = false;
};

