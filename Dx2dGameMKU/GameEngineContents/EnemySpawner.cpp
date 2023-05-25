#include "PrecompileHeader.h"
#include "EnemySpawner.h"

#include "RCGEnums.h"

#include "FieldLevelBase.h"
#include "BackGround.h"

#include "FieldEnemy_SchoolBoy.h"
#include "FieldEnemy_SchoolGirl.h"
#include "FieldEnemy_Cheerleader.h"
#include "FieldEnemy_Cop.h"
#include "FieldEnemy_Hooligan.h"
#include "FieldEnemy_TigerMan.h"
#include "FieldEnemy_Waver.h"

EnemySpawner::EnemySpawner(FieldLevelBase* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("EnemySpawner에 지정해준 레벨이 nullptr입니다");
		return;
	}

	Level = _Level;
	Enemies.reserve(30);
}

EnemySpawner::~EnemySpawner()
{
	if (nullptr != Level)
	{
		Level = nullptr;
	}
}


void EnemySpawner::CreateEnemies(const std::vector<EnemyCreateParameter>& _CreateInfoes)
{
	for (const EnemyCreateParameter& Info : _CreateInfoes)
	{
		CreateEnemy(Info.Type, Info.Pos);
	}
}

void EnemySpawner::CreateEnemy(EnemyType _Type, const float4& _CreatePos)
{
	std::shared_ptr<BackGround> BGPtr = Level->GetBackGround();
	std::shared_ptr<FieldEnemyBase> EnemyPtr = nullptr;
	
	//위치 조정
	switch (_Type)
	{
	case EnemyType::SchoolBoy:
		EnemyPtr = Level->CreateActor<FieldEnemy_SchoolBoy>(UpdateOrder::Enemy);
		break;
	case EnemyType::SchoolGirl:
		EnemyPtr = Level->CreateActor<FieldEnemy_SchoolGirl>(UpdateOrder::Enemy);
		break;
	case EnemyType::Cheerleader:
		EnemyPtr = Level->CreateActor<FieldEnemy_Cheerleader>(UpdateOrder::Enemy);
		break;
	case EnemyType::Cop:
		EnemyPtr = Level->CreateActor<FieldEnemy_Cop>(UpdateOrder::Enemy);
		break;
	case EnemyType::Hooligan:
		EnemyPtr = Level->CreateActor<FieldEnemy_Hooligan>(UpdateOrder::Enemy);
		break;
	case EnemyType::TigerMan:
		EnemyPtr = Level->CreateActor<FieldEnemy_TigerMan>(UpdateOrder::Enemy);
		break;
	case EnemyType::Waver:
		EnemyPtr = Level->CreateActor<FieldEnemy_Waver>(UpdateOrder::Enemy);
		break;
	}

	//생성
	float4 Pos = _CreatePos;
	Pos.z = Pos.y;
	EnemyPtr->GetTransform()->SetLocalPosition(Pos);
	EnemyPtr->SetSpawnIdx(Enemies.size());


	//자료구조에 저장
	EnemyDataBlock& Date = Enemies.emplace_back();
	Date.EnemyPtr = EnemyPtr;
	Date.GridPos = BGPtr->GetGridFromPos(Pos);
}




bool EnemySpawner::CheckValidIndex(std::shared_ptr<FieldEnemyBase> _Enemy)
{
	if (nullptr == _Enemy)
	{
		MsgAssert("인자로 nullptr인 FieldEnemyBase가 들어왔습니다");
		return false;
	}

	size_t EnemyIndex = _Enemy->GetSpawnID();
	if (Enemies.size() <= EnemyIndex)
	{
		MsgAssert("이 Enemy는 EnemySpawner를 통해 만들어진 Enemy가 아닙니다");
		return false;
	}

	EnemyDataBlock& Data = Enemies[EnemyIndex];
	if (Data.EnemyPtr.get() != _Enemy.get())
	{
		MsgAssert("이 Enemy는 EnemySpawner를 통해 만들어진 Enemy가 아닙니다");
		return false;
	}

	return true;
}


void EnemySpawner::KillEnemy(std::shared_ptr<FieldEnemyBase> _Enemy)
{
	CheckValidIndex(_Enemy);

	//자료구조에서 죽이려는 Enemy찾기
	size_t EnemyIndex = _Enemy->GetSpawnID();
	EnemyDataBlock& Data = Enemies[EnemyIndex];

	//죽이기 작업
	Data.EnemyPtr = nullptr;
	Data.IsDeath = true;
	++KillCount;

	//모든 Enemy를 다 죽인 경우에만
	if (KillCount != Enemies.size())
		return;

	if (nullptr == Callback)
		return;

	//콜백 호출
	Callback();
	Callback = nullptr;
}

void EnemySpawner::MarkGridPos(std::shared_ptr<FieldEnemyBase> _Enemy, const std::pair<int, int>& _Pos)
{
	CheckValidIndex(_Enemy);

	//인자로 들어온 Enemy의 데이터 블럭
	size_t EnemyIndex = _Enemy->GetSpawnID();
	EnemyDataBlock& Data = Enemies[EnemyIndex];

	//데이터 블럭에 GridPos 기록
	Data.GridPos = _Pos;
}


bool EnemySpawner::IsOtherStay(
	std::shared_ptr<FieldEnemyBase> _Enemy,
	const std::pair<int, int>& _NextPos,
	const std::pair<int, int>& _Volume /*= std::pair<int, int>{ 0, 0 }*/)
{
	CheckValidIndex(_Enemy);
	
	//인자로 들어온 Enemy의 데이터 블럭
	size_t EnemyIndex = _Enemy->GetSpawnID();
	std::pair<int, int> CheckGrid;

	for (size_t i = 0; i < Enemies.size(); ++i)
	{
		//이동하려는 Enemy의 위치는 제외(자기자신은 제외)
		if (i == EnemyIndex)
			continue;

		//죽은 Enemy는 제외
		if (true == Enemies[i].IsDeath)
			continue;

		//이동하려는 위치에 다른 Enemy가 존재하는 경우
		if (_NextPos == Enemies[i].GridPos)
			return true;

		CheckGrid = Enemies[i].GridPos;
		//이동하려는 위치가 범위보다 왼쪽인 경우
		if (_NextPos.first < (CheckGrid.first - _Volume.first))
			continue;

		//이동하려는 위치가 범위보다 오른쪽인 경우
		if ((CheckGrid.first + _Volume.first) < _NextPos.first)
			continue;

		//이동하려는 위치가 범위보다 아래쪽인 경우
		if (_NextPos.second < (CheckGrid.second - _Volume.second))
			continue;

		//이동하려는 위치가 범위보다 위쪽인 경우
		if ((CheckGrid.second + _Volume.second) < _NextPos.second)
			continue;

		//이동하려는 위치가 범위 안쪽으로 들어온 경우
		return true;
	}

	return false;
}