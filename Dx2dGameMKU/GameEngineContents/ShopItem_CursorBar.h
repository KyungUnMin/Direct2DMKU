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

	inline void SetMax(size_t _MaxCount)
	{
		MaxCursor = _MaxCount;
	}

	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	static const std::string_view BarRenderName;
	static const std::string_view ConfirmRenderName;

	static const float4 BarRenderScale;
	static const float4 ConfirmRenderScale;

	static const float4 ShopBarFirstPos;
	static const float4 ShopBarLastPos;
	static const float4 GymBarFirstPos;
	static const float4 GymBarLastPos;

	static const float4 ConfirmInnerOffset;
	static const float4 ConfirmOutOffset;

	GameEngineTransform* ConfirmBoxTrans = nullptr;

	float4 BarFirstPos = ShopBarFirstPos;
	float4 BarLastPos = ShopBarLastPos;

	size_t CurrentIndex = 0;
	size_t MaxCursor = 3;

	bool IsConfirmation = false;
	float ConfirmTime = FLT_MAX;

	inline void SetBarPos(const float4& _FirstPos, const float4& _LastPos)
	{
		BarFirstPos = _FirstPos;
		BarLastPos = _LastPos;
	}

	void Update_Move();
	void Update_Comfirm(float _DeltaTime);
};

