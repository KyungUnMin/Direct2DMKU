#pragma once

/*
Enemy의 생성/소멸을 관리해준다
*/

class FieldLevelBase;
class FieldEnemyBase;
class GameEngineRenderer;

enum class EnemyType
{
	SchoolBoy,
	SchoolGirl,
	Cheerleader,
	Cop,
	Hooligan,
	TigerMan,
	Waver,
};

struct EnemyCreateParameter
{
	EnemyType Type = EnemyType::SchoolBoy;
	float4 Pos = float4::Zero;
};

class EnemySpawner
{
public:
	EnemySpawner(FieldLevelBase* _Level);
	~EnemySpawner();

	EnemySpawner(const EnemySpawner& _Other) = delete;
	EnemySpawner(EnemySpawner&& _Other) noexcept = delete;
	EnemySpawner& operator=(const EnemySpawner& _Other) = delete;
	EnemySpawner& operator=(const EnemySpawner&& _Other) noexcept = delete;

	void CreateEnemies(const std::vector<EnemyCreateParameter>& _CreateInfoes);

	
	std::shared_ptr<FieldEnemyBase> CreateEnemy(EnemyType _Type,const float4& _CreatePos);


	inline void SetAllKillCallback(std::function<void()> _Callback)
	{
		if (false == CycleSpawnTypes.empty())
		{
			MsgAssert("몬스터를 주기적으로 생성하는 EnemySpawner는 AllKill콜백함수를 등록할 수 없습니다");
			return;
		}
		
		Callback = _Callback;
	}

	//Enemy 죽이기
	void KillEnemy(std::shared_ptr<FieldEnemyBase> _Enemy);

	
	//Enemy의 위치 기록하기
	void MarkGridPos(std::shared_ptr<FieldEnemyBase> _Enemy, const std::pair<int,int>& _Pos);


	//_Enemy가 이동하려는 위치인 _NextPos에 다른 Enemy가 존재하는지 확인하는 함수
	bool IsOtherStay(
		std::shared_ptr<FieldEnemyBase> _Enemy,
		const std::pair<int, int>& _NextPos,
		int _CheckArea = 0);

	

	//해당 레벨에서 몬스터를 주기적으로 생성할 때 호출
	void OnCycleSpawn(const std::vector<EnemyType>& _SpawnTypes, const std::vector<float4>& _SpawnPoses);


	void Update(float _DeltaTime);

	inline void SetCycleDuration(float _MinDuration, float _MaxDuration)
	{
		MinDuration = _MinDuration;
		MaxDuration = _MaxDuration;
	}

	inline void SetCycleMax(size_t _MaxSpawnCount)
	{
		MaxSpawnCount = _MaxSpawnCount;
	}

	//(혹시나 나중에 문제 생기면 FleldLevelBase::LevelChangeEnd에서 이 함수를 호출시키지 말자)
	//내부 자료구조를 청소한다
	void ClearDeathEnemy();

protected:

private:
	struct EnemyDataBlock
	{
		std::shared_ptr<FieldEnemyBase> EnemyPtr = nullptr;
		bool IsDeath = false;
		std::pair<int, int> GridPos;
	};

	std::vector<EnemyDataBlock> Enemies;
	FieldLevelBase* Level = nullptr;

	
	size_t KillCount = 0;
	std::function<void()> Callback = nullptr;

	float Timer = 0.f;
	float Duration = 0.f;
	float MinDuration = 1.f;
	float MaxDuration = 10.f;
	size_t MaxSpawnCount = 10;

	const float4 SpawnPosColor = float4{ 0.f, 0.f, 1.f, 0.5f };
	bool IsCycleSpawnRenderOnValue = false;

	size_t SpawnIndex = 0;
	std::vector<EnemyType> CycleSpawnTypes;
	std::vector<std::shared_ptr<GameEngineRenderer>> SpawnPoses;

	bool CheckValidIndex(std::shared_ptr<FieldEnemyBase> _Enemy);

	//스폰 위치 디버깅렌더러 On/Off 처리
	void Update_DebugRender();
};

