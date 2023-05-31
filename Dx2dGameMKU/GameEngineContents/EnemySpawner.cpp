#include "PrecompileHeader.h"
#include "EnemySpawner.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"

#include "FieldLevelBase.h"
#include "BackGround.h"
#include "DebugActor.h"

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

std::shared_ptr<FieldEnemyBase> EnemySpawner::CreateEnemy(EnemyType _Type, const float4& _CreatePos)
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


	return EnemyPtr;
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

	if ((_Enemy.get() != Data.EnemyPtr.get()) || (true == Data.IsDeath))
	{
		MsgAssert("EnemySpawner�� �߸��� Enemy�� ��ϵǾ� �ְų�, �̹� ���� Enemy�� �� ���Ϸ��� �߽��ϴ�");
		return;
	}

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
	int _CheckArea /*= 0*/)
{
	CheckValidIndex(_Enemy);
	
	float4 PrevFieldPos = _Enemy->GetTransform()->GetWorldPosition();

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

		if (0 == _CheckArea)
			continue;

		CheckGrid = Enemies[i].GridPos;
		//�̵��Ϸ��� ��ġ�� �������� ������ ���
		if (_NextPos.first < (CheckGrid.first - _CheckArea))
			continue;

		//�̵��Ϸ��� ��ġ�� �������� �������� ���
		if ((CheckGrid.first + _CheckArea) < _NextPos.first)
			continue;

		//�̵��Ϸ��� ��ġ�� �������� �Ʒ����� ���
		if (_NextPos.second < (CheckGrid.second - _CheckArea))
			continue;

		//�̵��Ϸ��� ��ġ�� �������� ������ ���
		if ((CheckGrid.second + _CheckArea) < _NextPos.second)
			continue;

		return true;
	}

	return false;
}







void EnemySpawner::OnCycleSpawn(const std::vector<EnemyType>& _SpawnTypes, const std::vector<float4>& _SpawnPoses)
{
	if (nullptr != Callback)
	{
		MsgAssert("���͸� �ֱ������� �����ϴ� EnemySpawner�� AllKill�ݹ��Լ��� ����� �� �����ϴ�");
		return;
	}


	std::shared_ptr<BackGround> BGPtr = Level->GetBackGround();
	std::shared_ptr<GameEngineActor> Debuger = Level->CreateActor<DebugActor>(UpdateOrder::Defalut);


	//�׸��� ������ �˾ƿ���
	const float4& GridScale = BGPtr->GetGridScale();
	if (true == GridScale.IsZero())
	{
		MsgAssert("BackGround�� GridScale�� �˾ƿ��� ���� BackGround�� �ʱ�ȭ�� ���ְ� EnemySpawner::OnCycleSpawn�� ȣ�����־�� �մϴ�");
		return;
	}


	CycleSpawnTypes = _SpawnTypes;
	SpawnPoses.resize(_SpawnPoses.size(), nullptr);

	//�Է¹��� ������ ��ġ�� Renderer����
	std::shared_ptr<GameEngineRenderer> Render = nullptr;
	for (size_t i = 0; i < _SpawnPoses.size(); ++i)
	{
		Render = Debuger->CreateComponent<GameEngineRenderer>(FieldRenderOrder::Debug_Grid);
		GameEngineTransform* RenderTrans = Render->GetTransform();

		//ũ�� �׸��� �����Ϸ� ����
		RenderTrans->SetWorldScale(GridScale);

		//�Է¹��� ��ġ�� �׸��忡 �� �°� ����
		std::pair<int, int> GridPos = BGPtr->GetGridFromPos(_SpawnPoses[i]);
		float4 Pos = BGPtr->GetPosFromGrid(GridPos.first, GridPos.second);
		Pos.z = -499.f;
		RenderTrans->SetWorldPosition(Pos);

		//�ؽ�ó ����
		Render->SetPipeLine("DirectColor");
		Render->GetShaderResHelper().SetConstantBufferLink("LinkColor", SpawnPosColor);
		Render->Off();

		SpawnPoses[i] = Render;
	}
	

	if (true == CycleSpawnTypes.empty())
	{
		MsgAssert("�ֱ������� Enemy�� �����Ϸ��� �� �� �����Ϸ��� EnemyType�� ���������� �ʾҽ��ϴ�");
		return;
	}

	if (true == SpawnPoses.empty())
	{
		MsgAssert("�ֱ������� Enemy�� �����Ϸ��� �� �� ������ġ�� ���������� �ʾҽ��ϴ�");
		return;
	}

}




void EnemySpawner::Update(float _DeltaTime)
{
	//Enemy�� �ֱ������� ������Ű�� EnemySpawner�� ��쿡��
	if (true == CycleSpawnTypes.empty())
		return;

	//���� ��ġ ����뷻���� On/Off ó��
	Update_DebugRender();
	

	//Enemy�� �ִ� ���� ����
	size_t CurEnemyCount = Enemies.size() - KillCount;
	if (MaxSpawnCount <= CurEnemyCount)
		return;


	//Spawn �ð�
	Timer += _DeltaTime;
	if (Timer < Duration)
		return;


	//� Enemy�� ������ ������
	int CreateIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(CycleSpawnTypes.size() - 1));
	EnemyType CreateEnemyType = CycleSpawnTypes[CreateIndex];
	
	//� ��ġ�� ������ ������
	int PosIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SpawnPoses.size() - 1));
	GameEngineTransform* SpawnPosRenderTrans = SpawnPoses[PosIndex]->GetTransform();
	float4 SpawnPos = SpawnPosRenderTrans->GetWorldPosition();
	std::pair<int, int> GridSpawnPos = Level->GetBackGround()->GetGridFromPos(SpawnPos);

	//�����Ϸ��� ��ġ�� �ٸ� Enemy�� �����Ѵٸ� �������� ����
	for (const EnemyDataBlock& Enemy : Enemies)
	{
		//���� Enemy���� ����
		if (true == Enemy.IsDeath)
			continue;

		//�����Ϸ��� ��ġ�� �ٸ� Enemy�� �����ϴ� ���(���� �����ӿ� �ٸ� ������ ��ġ�� ����)
		if (Enemy.GridPos == GridSpawnPos)
			return;
	}

	
	CreateEnemy(CreateEnemyType, SpawnPosRenderTrans->GetWorldPosition());

	Timer -= Duration;
	Duration = GameEngineRandom::MainRandom.RandomFloat(MinDuration, MaxDuration);
}

void EnemySpawner::Update_DebugRender()
{
	//����� Ű�� ��������
	if (false == KeyMgr::IsDown(KeyNames::DebugF2))
		return;


	IsCycleSpawnRenderOnValue = !IsCycleSpawnRenderOnValue;

	//����� On�̶��
	if (true == IsCycleSpawnRenderOnValue)
	{
		//���� ��ġ ������ �ѱ�
		for (std::shared_ptr<GameEngineRenderer> SpawnPos : SpawnPoses)
		{
			SpawnPos->On();
		}
	}

	//����� Off���
	else
	{
		//���� ��ġ ������ ����
		for (std::shared_ptr<GameEngineRenderer> SpawnPos : SpawnPoses)
		{
			SpawnPos->Off();
		}
	}

}