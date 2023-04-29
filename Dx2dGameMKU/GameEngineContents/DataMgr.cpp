#include "PrecompileHeader.h"
#include "DataMgr.h"

const int DataMgr::PlayerFullHp = 100;
int DataMgr::PlayerHp = PlayerFullHp;
std::vector<ItemType> DataMgr::Inventory(8, ItemType::Empty);

DataMgr::DataMgr()
{

}

DataMgr::~DataMgr()
{

}
