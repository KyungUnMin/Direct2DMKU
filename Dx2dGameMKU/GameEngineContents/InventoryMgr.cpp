#include "PrecompileHeader.h"
#include "InventoryMgr.h"

std::list<InvenItemType> InventoryMgr::Inven;
const size_t InventoryMgr::MaxCount = 10;

bool InventoryMgr::IsFull()
{
	return MaxCount <= Inven.size();
}


void InventoryMgr::PushItem(InvenItemType _Item)
{
	//�κ��丮 ���� ����
	if (true == IsFull())
	{
		MsgAssert("�κ��丮�� ���� ������ ���µ�, �������� �������� �߽��ϴ�");
		return;
	}

	Inven.push_back(_Item);
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
		MsgAssert("�������� �ʴ� �������� �����ҷ��� �߽��ϴ�");
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
