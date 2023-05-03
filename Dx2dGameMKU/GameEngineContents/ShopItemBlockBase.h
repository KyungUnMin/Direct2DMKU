#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class ShopItemBlockBase : public GameEngineActor
{
public:
	ShopItemBlockBase();
	virtual ~ShopItemBlockBase() = 0;

	ShopItemBlockBase(const ShopItemBlockBase& _Other) = delete;
	ShopItemBlockBase(ShopItemBlockBase&& _Other) noexcept = delete;
	ShopItemBlockBase& operator=(const ShopItemBlockBase& _Other) = delete;
	ShopItemBlockBase& operator=(const ShopItemBlockBase&& _Other) noexcept = delete;

	virtual void HoverIn(){}
	virtual void HoverOut(){}
	virtual void Buy() = 0;

protected:
	void Init(
		const std::string_view& _Name, const std::string_view& _Description,
		const std::string_view& _TextureName, int _Cost, std::function<void()> _CallBack);

	void ChangeDescription(const std::string_view& _Desc);

	void CallBackExcute();

	inline std::shared_ptr<GameEngineSpriteRenderer> GetTexture() const
	{
		return Texture;
	}

	bool MoneyCheck();

private:
	std::string_view Name = "UNKNOWN";
	std::string Description = "";
	std::shared_ptr<GameEngineSpriteRenderer> Texture = nullptr;

	int Cost = INT32_MAX;
	std::function<void()> CallBack = nullptr;
};

