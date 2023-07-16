#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;

enum class ShopResultType
{
	BuyOk,
	MoneyLack,
	InvenLack,
	LevelLack,
	SoldOut,
};

class ShopUI_ResultText : public GameEngineActor
{
public:
	static ShopUI_ResultText* GPtr;

	static ShopUI_ResultText* GetGPtr()
	{
		if (nullptr == GPtr)
		{
			MsgAssert("ShopUI_ResultText의 전역 포인터가 nullptr입니다");
			return nullptr;
		}

		return GPtr;
	}

	ShopUI_ResultText();
	~ShopUI_ResultText() override;

	ShopUI_ResultText(const ShopUI_ResultText& _Other) = delete;
	ShopUI_ResultText(ShopUI_ResultText&& _Other) noexcept = delete;
	ShopUI_ResultText& operator=(const ShopUI_ResultText& _Other) = delete;
	ShopUI_ResultText& operator=(const ShopUI_ResultText&& _Other) noexcept = delete;

	void TextOn(ShopResultType _Result);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;

private:
	static std::vector<std::string_view> TexNames;

	std::shared_ptr<GameEngineUIRenderer> TextRender = nullptr;

};

