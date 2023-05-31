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

std::shared_ptr<FieldEnemyBase> EnemySpawner::CreateEnemy(EnemyType _Type, const float4& _CreatePos)
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


	return EnemyPtr;
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

	if ((_Enemy.get() != Data.EnemyPtr.get()) || (true == Data.IsDeath))
	{
		MsgAssert("EnemySpawner에 잘못된 Enemy가 등록되어 있거나, 이미 죽은 Enemy를 또 죽일려고 했습니다");
		return;
	}

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
	int _CheckArea /*= 0*/)
{
	CheckValidIndex(_Enemy);
	
	float4 PrevFieldPos = _Enemy->GetTransform()->GetWorldPosition();

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

		if (0 == _CheckArea)
			continue;

		CheckGrid = Enemies[i].GridPos;
		//이동하려는 위치가 범위보다 왼쪽인 경우
		if (_NextPos.first < (CheckGrid.first - _CheckArea))
			continue;

		//이동하려는 위치가 범위보다 오른쪽인 경우
		if ((CheckGrid.first + _CheckArea) < _NextPos.first)
			continue;

		//이동하려는 위치가 범위보다 아래쪽인 경우
		if (_NextPos.second < (CheckGrid.second - _CheckArea))
			continue;

		//이동하려는 위치가 범위보다 위쪽인 경우
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
		MsgAssert("몬스터를 주기적으로 생성하는 EnemySpawner는 AllKill콜백함수를 등록할 수 없습니다");
		return;
	}


	std::shared_ptr<BackGround> BGPtr = Level->GetBackGround();
	std::shared_ptr<GameEngineActor> Debuger = Level->CreateActor<DebugActor>(UpdateOrder::Defalut);


	//그리드 스케일 알아오기
	const float4& GridScale = BGPtr->GetGridScale();
	if (true == GridScale.IsZero())
	{
		MsgAssert("BackGround의 GridScale을 알아오기 위해 BackGround를 초기화를 해주고 EnemySpawner::OnCycleSpawn를 호출해주어야 합니다");
		return;
	}


	CycleSpawnTypes = _SpawnTypes;
	SpawnPoses.resize(_SpawnPoses.size(), nullptr);

	//입력받은 스포너 위치에 Renderer생성
	std::shared_ptr<GameEngineRenderer> Render = nullptr;
	for (size_t i = 0; i < _SpawnPoses.size(); ++i)
	{
		Render = Debuger->CreateComponent<GameEngineRenderer>(FieldRenderOrder::Debug_Grid);
		GameEngineTransform* RenderTrans = Render->GetTransform();

		//크기 그리드 스케일로 지정
		RenderTrans->SetWorldScale(GridScale);

		//입력받은 위치를 그리드에 딱 맞게 지정
		std::pair<int, int> GridPos = BGPtr->GetGridFromPos(_SpawnPoses[i]);
		float4 Pos = BGPtr->GetPosFromGrid(GridPos.first, GridPos.second);
		Pos.z = -499.f;
		RenderTrans->SetWorldPosition(Pos);

		//텍스처 생성
		Render->SetPipeLine("DirectColor");
		Render->GetShaderResHelper().SetConstantBufferLink("LinkColor", SpawnPosColor);
		Render->Off();

		SpawnPoses[i] = Render;
	}
	

	if (true == CycleSpawnTypes.empty())
	{
		MsgAssert("주기적으로 Enemy를 생성하려고 할 때 생성하려는 EnemyType를 지정해주지 않았습니다");
		return;
	}

	if (true == SpawnPoses.empty())
	{
		MsgAssert("주기적으로 Enemy를 생성하려고 할 때 생성위치를 지정해주지 않았습니다");
		return;
	}

}




void EnemySpawner::Update(float _DeltaTime)
{
	//Enemy를 주기적으로 생성시키는 EnemySpawner인 경우에만
	if (true == CycleSpawnTypes.empty())
		return;

	//스폰 위치 디버깅렌더러 On/Off 처리
	Update_DebugRender();
	

	//Enemy의 최대 갯수 제한
	size_t CurEnemyCount = Enemies.size() - KillCount;
	if (MaxSpawnCount <= CurEnemyCount)
		return;


	//Spawn 시간
	Timer += _DeltaTime;
	if (Timer < Duration)
		return;


	//어떤 Enemy를 생성할 것인지
	int CreateIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(CycleSpawnTypes.size() - 1));
	EnemyType CreateEnemyType = CycleSpawnTypes[CreateIndex];
	
	//어떤 위치에 생성할 것인지
	int PosIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(SpawnPoses.size() - 1));
	GameEngineTransform* SpawnPosRenderTrans = SpawnPoses[PosIndex]->GetTransform();
	float4 SpawnPos = SpawnPosRenderTrans->GetWorldPosition();
	std::pair<int, int> GridSpawnPos = Level->GetBackGround()->GetGridFromPos(SpawnPos);

	//생성하려는 위치에 다른 Enemy가 존재한다면 생성하지 않음
	for (const EnemyDataBlock& Enemy : Enemies)
	{
		//죽은 Enemy들은 제외
		if (true == Enemy.IsDeath)
			continue;

		//생성하려는 위치에 다른 Enemy가 존재하는 경우(다음 프레임에 다른 랜덤한 위치에 생성)
		if (Enemy.GridPos == GridSpawnPos)
			return;
	}

	
	CreateEnemy(CreateEnemyType, SpawnPosRenderTrans->GetWorldPosition());

	Timer -= Duration;
	Duration = GameEngineRandom::MainRandom.RandomFloat(MinDuration, MaxDuration);
}

void EnemySpawner::Update_DebugRender()
{
	//디버깅 키를 누를때만
	if (false == KeyMgr::IsDown(KeyNames::DebugF2))
		return;


	IsCycleSpawnRenderOnValue = !IsCycleSpawnRenderOnValue;

	//디버그 On이라면
	if (true == IsCycleSpawnRenderOnValue)
	{
		//스폰 위치 렌더러 켜기
		for (std::shared_ptr<GameEngineRenderer> SpawnPos : SpawnPoses)
		{
			SpawnPos->On();
		}
	}

	//디버그 Off라면
	else
	{
		//스폰 위치 렌더러 끄기
		for (std::shared_ptr<GameEngineRenderer> SpawnPos : SpawnPoses)
		{
			SpawnPos->Off();
		}
	}

}