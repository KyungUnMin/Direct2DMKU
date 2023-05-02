#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ShopItem_CursorBar : public GameEngineActor
{
public:
	ShopItem_CursorBar();
	~ShopItem_CursorBar() override;

	ShopItem_CursorBar(const ShopItem_CursorBar& _Other) = delete;
	ShopItem_CursorBar(ShopItem_CursorBar&& _Other) noexcept = delete;
	ShopItem_CursorBar& operator=(const ShopItem_CursorBar& _Other) = delete;
	ShopItem_CursorBar& operator=(const ShopItem_CursorBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float4 BarRenderScale;
	static const std::string_view BarRenderName;
	static const float4 BarFirstPos;
	static const float4 BarLastPos;

	size_t CurrentIndex = 0;
};

