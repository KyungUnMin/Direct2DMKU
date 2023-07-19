#include "PrecompileHeader.h"
#include "DataMgr.h"

const int DataMgr::PlayerFullPoint = 100;
int DataMgr::PlayerHp = PlayerFullPoint;
int DataMgr::PlayerMp = 0;
int DataMgr::PlayerMoney = 0;

float DataMgr::PlayerSpeedPer = 1.f;
int DataMgr::PlayerAtt = 1;
bool DataMgr::IsUnbeatable = false;


int DataMgr::PlayerLevel = 1;
int DataMgr::PlayerExp = 0;
std::list<std::function<bool(void)>> DataMgr::LevelUpCallBacks;

//std::vector<ItemType> DataMgr::Inventory(8, ItemType::Empty);

DataMgr::DataMgr()
{

}

DataMgr::~DataMgr()
{

}

void DataMgr::PlayerLevelUp()
{
	++PlayerAtt;
	++PlayerLevel;
	PlayerSpeedPer += 0.01f;

	PlayerHp = PlayerFullPoint;
	PlayerMp = PlayerFullPoint;

	std::list<std::function<bool(void)>>::iterator StartIter = LevelUpCallBacks.begin();
	std::list<std::function<bool(void)>>::iterator EndiIter = LevelUpCallBacks.end();

	while (StartIter != EndiIter)
	{
		std::function<bool(void)> CallBack = (*StartIter);
		if (nullptr == CallBack)
		{
			MsgAssert("레벨업 콜백에 등록한 함수가 nullptr입니다");
			return;
		}

		bool IsErase = CallBack();
		if (true == IsErase)
		{
			StartIter = LevelUpCallBacks.erase(StartIter);
		}
		else
		{
			++StartIter;
		}
	}
}
