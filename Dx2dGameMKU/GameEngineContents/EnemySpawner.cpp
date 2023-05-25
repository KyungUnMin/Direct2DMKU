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
		MsgAssert("EnemySpawner�� �������� ������ nullptr�Դϴ�");
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
	
	//��ġ ����
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

	//����
	float4 Pos = _CreatePos;
	Pos.z = Pos.y;
	EnemyPtr->GetTransform()->SetLocalPosition(Pos);
	EnemyPtr->SetSpawnIdx(Enemies.size());


	//�ڷᱸ���� ����
	EnemyDataBlock& Date = Enemies.emplace_back();
	Date.EnemyPtr = EnemyPtr;
	Date.GridPos = BGPtr->GetGridFromPos(Pos);
}




bool EnemySpawner::CheckValidIndex(std::shared_ptr<FieldEnemyBase> _Enemy)
{
	if (nullptr == _Enemy)
	{
		MsgAssert("���ڷ� nullptr�� FieldEnemyBase�� ���Խ��ϴ�");
		return false;
	}

	size_t EnemyIndex = _Enemy->GetSpawnID();
	if (Enemies.size() <= EnemyIndex)
	{
		MsgAssert("�� Enemy�� EnemySpawner�� ���� ������� Enemy�� �ƴմϴ�");
		return false;
	}

	EnemyDataBlock& Data = Enemies[EnemyIndex];
	if (Data.EnemyPtr.get() != _Enemy.get())
	{
		MsgAssert("�� Enemy�� EnemySpawner�� ���� ������� Enemy�� �ƴմϴ�");
		return false;
	}

	return true;
}


void EnemySpawner::KillEnemy(std::shared_ptr<FieldEnemyBase> _Enemy)
{
	CheckValidIndex(_Enemy);

	//�ڷᱸ������ ���̷��� Enemyã��
	size_t EnemyIndex = _Enemy->GetSpawnID();
	EnemyDataBlock& Data = Enemies[EnemyIndex];

	//���̱� �۾�
	Data.EnemyPtr = nullptr;
	Data.IsDeath = true;
	++KillCount;

	//��� Enemy�� �� ���� ��쿡��
	if (KillCount != Enemies.size())
		return;

	if (nullptr == Callback)
		return;

	//�ݹ� ȣ��
	Callback();
	Callback = nullptr;
}

void EnemySpawner::MarkGridPos(std::shared_ptr<FieldEnemyBase> _Enemy, const std::pair<int, int>& _Pos)
{
	CheckValidIndex(_Enemy);

	//���ڷ� ���� Enemy�� ������ ��
	size_t EnemyIndex = _Enemy->GetSpawnID();
	EnemyDataBlock& Data = Enemies[EnemyIndex];

	//������ ���� GridPos ���
	Data.GridPos = _Pos;
}


bool EnemySpawner::IsOtherStay(
	std::shared_ptr<FieldEnemyBase> _Enemy,
	const std::pair<int, int>& _NextPos,
	const std::pair<int, int>& _Volume /*= std::pair<int, int>{ 0, 0 }*/)
{
	CheckValidIndex(_Enemy);
	
	//���ڷ� ���� Enemy�� ������ ��
	size_t EnemyIndex = _Enemy->GetSpawnID();
	std::pair<int, int> CheckGrid;

	for (size_t i = 0; i < Enemies.size(); ++i)
	{
		//�̵��Ϸ��� Enemy�� ��ġ�� ����(�ڱ��ڽ��� ����)
		if (i == EnemyIndex)
			continue;

		//���� Enemy�� ����
		if (true == Enemies[i].IsDeath)
			continue;

		//�̵��Ϸ��� ��ġ�� �ٸ� Enemy�� �����ϴ� ���
		if (_NextPos == Enemies[i].GridPos)
			return true;

		CheckGrid = Enemies[i].GridPos;
		//�̵��Ϸ��� ��ġ�� �������� ������ ���
		if (_NextPos.first < (CheckGrid.first - _Volume.first))
			continue;

		//�̵��Ϸ��� ��ġ�� �������� �������� ���
		if ((CheckGrid.first + _Volume.first) < _NextPos.first)
			continue;

		//�̵��Ϸ��� ��ġ�� �������� �Ʒ����� ���
		if (_NextPos.second < (CheckGrid.second - _Volume.second))
			continue;

		//�̵��Ϸ��� ��ġ�� �������� ������ ���
		if ((CheckGrid.second + _Volume.second) < _NextPos.second)
			continue;

		//�̵��Ϸ��� ��ġ�� ���� �������� ���� ���
		return true;
	}

	return false;
}