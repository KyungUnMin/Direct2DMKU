#pragma once

enum class InvenItemType
{
	Candy,
	CottonCandy,
	GummyYummi,
	MelonMint,

	DoubleBurger,
	SingleBurger,
	TeckFried,
	TeckShake
};



class InventoryMgr
{
public:
	static bool IsFull();
	static void PushItem(InvenItemType _Item);

	static std::vector<InvenItemType> GetItems();

	static void Erase(InvenItemType _Item);

	InventoryMgr(const InventoryMgr& _Other) = delete;
	InventoryMgr(InventoryMgr&& _Other) noexcept = delete;
	InventoryMgr& operator=(const InventoryMgr& _Other) = delete;
	InventoryMgr& operator=(const InventoryMgr&& _Other) noexcept = delete;

protected:

private:
	static std::list<InvenItemType> Inven;
	static const size_t MaxCount;

	

	InventoryMgr();
	virtual ~InventoryMgr() = 0;
};

