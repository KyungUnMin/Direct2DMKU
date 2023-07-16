#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
enum class ShopResultType;

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

	virtual ShopResultType IsAvailable() = 0;
	virtual void Buy() = 0;
	virtual void Reset() {};

	inline const std::string& GetInfoTexName() const
	{
		return InfoTexName;
	}

	inline int GetIndex() const
	{
		return Index;
	}

	

protected:
	void Init(
		const std::string_view& _CursorTexName,
		const std::string_view& _IconTexName,
		int _Cost, int _Index, std::function<void()> _CallBack);


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

	inline int GetCost() const
	{
		return Cost;
	}

private:
	std::shared_ptr<GameEngineUIRenderer> IconRender = nullptr;
	std::string CursorTexName;
	std::string InfoTexName;


	int Index = -1;
	int Cost = INT32_MAX;
	std::function<void()> CallBack = nullptr;

};

