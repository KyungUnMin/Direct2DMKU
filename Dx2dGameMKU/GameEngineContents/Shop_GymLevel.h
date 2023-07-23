#pragma once
#include "ShopLevelBase.h"

enum class PlayerStateType;

class Shop_GymLevel : public ShopLevelBase
{
public:
	Shop_GymLevel();
	~Shop_GymLevel() override;

	Shop_GymLevel(const Shop_GymLevel& _Other) = delete;
	Shop_GymLevel(Shop_GymLevel&& _Other) noexcept = delete;
	Shop_GymLevel& operator=(const Shop_GymLevel& _Other) = delete;
	Shop_GymLevel& operator=(const Shop_GymLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	static const std::vector<PlayerStateType> UnlockSkills;

	int PrevSkillBit = -1;
	int NowSkillBit = -1;

};

