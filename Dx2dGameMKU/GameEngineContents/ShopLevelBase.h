#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class LevelNames;

class ShopLevelBase : public GameEngineLevel
{
	friend class LevelMgr;

public:
	ShopLevelBase();
	virtual ~ShopLevelBase() = 0;

	ShopLevelBase(const ShopLevelBase& _Other) = delete;
	ShopLevelBase(ShopLevelBase&& _Other) noexcept = delete;
	ShopLevelBase& operator=(const ShopLevelBase& _Other) = delete;
	ShopLevelBase& operator=(const ShopLevelBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SettingBackImage(const std::string_view& _BackImageName);

private:
	static LevelNames PrevLevel;

	void ImageResLoad();
};
