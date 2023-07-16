#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
enum class ShopResultType;

class ShopItem_CursorBar : public GameEngineActor
{
public:
	static const std::string_view ConfirmRenderName;

	static const float4 BarRenderScale;
	static const float4 ConfirmRenderScale;

	static const float4 ShopBarFirstPos;
	static const float4 ShopBarLastPos;
	static const float4 GymBarFirstPos;
	static const float4 GymBarLastPos;

	static const float4 ConfirmInnerOffset;
	static const float4 ConfirmOutOffset;

	static void ChangeCursorTex(const std::string_view& _CursorTex);


	ShopItem_CursorBar();
	~ShopItem_CursorBar() override;

	ShopItem_CursorBar(const ShopItem_CursorBar& _Other) = delete;
	ShopItem_CursorBar(ShopItem_CursorBar&& _Other) noexcept = delete;
	ShopItem_CursorBar& operator=(const ShopItem_CursorBar& _Other) = delete;
	ShopItem_CursorBar& operator=(const ShopItem_CursorBar&& _Other) noexcept = delete;

	static size_t GetCurrentIndex()
	{
		return CurrentIndex;
	}

	//레벨에서 ShopSlotController를 생성한 뒤에 반드시 호출시켜줘야 함
	void CreateItemDescRender();
	
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;

private:
	static size_t CurrentIndex;
	static std::weak_ptr<GameEngineUIRenderer> CursorBar;

	size_t MaxCursor = 39467;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> AllItemDesc;
	std::shared_ptr<GameEngineUIRenderer> BarRender = nullptr;
	GameEngineTransform* ConfirmBoxTrans = nullptr;

	float4 BarFirstPos = ShopBarFirstPos;
	float4 BarLastPos = ShopBarLastPos;

	bool IsConfirmation = false;
	float ConfirmTime = -1.f;

	inline void SetBarPos(const float4& _FirstPos, const float4& _LastPos)
	{
		BarFirstPos = _FirstPos;
		BarLastPos = _LastPos;
	}

	void Update_CursorMove();
	void Update_ComfirmMove(float _DeltaTime);
	bool InteractConfilm();

	void PerceiveCursorMove();
	void BuyItem();
	void SetResultText(ShopResultType _Result);
};

