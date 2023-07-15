#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;

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
		const std::string_view& _CursorTexName,
		const std::string_view& _IconTexName,
		int _Cost, std::function<void()> _CallBack);


	inline std::shared_ptr<GameEngineUIRenderer> GetIcon() const
	{
		return IconRender;
	}

	inline const std::string& GetCursorTexName() const
	{
		return CursorTexName;
	}

	bool MoneyCheck();

	void CallBackExcute();

private:
	std::shared_ptr<GameEngineUIRenderer> IconRender = nullptr;
	std::string CursorTexName;

	int Cost = INT32_MAX;
	std::function<void()> CallBack = nullptr;

};

