#include "PrecompileHeader.h"
#include "DataMgr.h"

const int DataMgr::PlayerFullPoint = 100;
int DataMgr::PlayerHp = PlayerFullPoint;
int DataMgr::PlayerMp = PlayerFullPoint;
int DataMgr::PlayerMoney = 0;

float DataMgr::PlayerSpeedPer = 1.f;
int DataMgr::PlayerAtt = 1;


int DataMgr::PlayerLevel = 1;
int DataMgr::PlayerExp = 0;
const int DataMgr::PlayerMaxExp = 100;

//std::vector<ItemType> DataMgr::Inventory(8, ItemType::Empty);

DataMgr::DataMgr()
{

}

DataMgr::~DataMgr()
{

}
