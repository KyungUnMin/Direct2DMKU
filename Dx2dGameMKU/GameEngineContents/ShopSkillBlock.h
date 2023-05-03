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

	void Init(const std::string_view& _Name, int _UnlockLevel,
		const std::string_view& _TextureName, int _Cost, std::function<void()> _CallBack)
	{
		UnlockLevel = _UnlockLevel;

		std::string Description = "언락 레벨 " + std::to_string(UnlockLevel);
		ShopItemBlockBase::Init(_Name, Description, "GymCheckIcon.png", _Cost, _CallBack);
	}


	void Buy() override;

protected:

private:
	int UnlockLevel = INT32_MAX;
	bool PrevAquired = false;
};

