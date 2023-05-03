#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ShopItemBlockBase;

class ShopSlotController : public GameEngineActor
{
public:
	static const size_t MaxSlot;

	ShopSlotController();
	~ShopSlotController() override;

	ShopSlotController(const ShopSlotController& _Other) = delete;
	ShopSlotController(ShopSlotController&& _Other) noexcept = delete;
	ShopSlotController& operator=(const ShopSlotController& _Other) = delete;
	ShopSlotController& operator=(const ShopSlotController&& _Other) noexcept = delete;

	inline void Reset()
	{
		PrevCursorIndex = 0;
	}

protected:
	void Start() override;
	void Update(float _DelatTime) override;

private:
	std::vector<std::shared_ptr<ShopItemBlockBase>> ItemBlocks;
	size_t PrevCursorIndex = 56789;


	void Init_Burger();
	void Init_Gym();
	void Init_Store();

	std::shared_ptr<ShopItemBlockBase> CreateItemBlock(
		const std::string_view& _Name,
		const std::string_view& _Description,
		const std::string_view& _TextureName,
		int _Cost, std::function<void()> _CallBack);

	std::shared_ptr<ShopItemBlockBase> CreateSkillBlock(
		const std::string_view& _Name, int _UnlockLevel,
		int _Cost, std::function<void()> _CallBack);


	void Update_Select();
	void Update_Buy();
};

