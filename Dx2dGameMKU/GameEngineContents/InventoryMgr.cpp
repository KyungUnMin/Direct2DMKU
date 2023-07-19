#include "PrecompileHeader.h"
#include "InventoryMgr.h"

std::list<InvenItemType> InventoryMgr::Inven;
const size_t InventoryMgr::MaxCount = 10;


bool InventoryMgr::PushItem(InvenItemType _Item)
{
	//인벤토리 공간 부족
	if (MaxCount <= Inven.size())
		return false;

	Inven.push_back(_Item);
	return true;
}

std::vector<InvenItemType> InventoryMgr::GetItems()
{
	std::vector<InvenItemType> AllItem;
	AllItem.reserve(Inven.size());

	for (InvenItemType Item : Inven)
	{
		AllItem.push_back(Item);
	}

	return AllItem;
}

void InventoryMgr::Erase(InvenItemType _Item)
{
	std::list<InvenItemType>::iterator FindIter = std::find(Inven.begin(), Inven.end(), _Item);
	if (Inven.end() == FindIter)
	{
		MsgAssert("존재하지 않는 아이템을 삭제할려고 했습니다");
		return;
	}

	Inven.erase(FindIter);
}




InventoryMgr::InventoryMgr()
{

}

InventoryMgr::~InventoryMgr()
{

}
