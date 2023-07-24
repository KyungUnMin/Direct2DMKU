#pragma once
#include "RCGEnums.h"


/*
Enemy�� ����/�Ҹ��� �������ش�
*/

class FieldLevelBase;
class FieldEnemyBase;
class GameEngineRenderer;

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



	//Enemy�� ��� óġ�Ҷ� ȣ��Ǵ� �ݹ�(��ȸ��)
	inline void SetAllKillCallback(std::function<void()> _Callback)
	{
		if (false == CycleSpawnTypes.empty())
		{
			MsgAssert("���͸� �ֱ������� �����ϴ� EnemySpawner�� AllKill�ݹ��Լ��� ����� �� �����ϴ�");
			return;
		}
		
		AllKillCallback = _Callback;
	}

	//Enemy�� óġ�Ҷ����� ȣ��Ǵ� �ݹ�(��ȸ���� �ƴϱ� ������ ������� �ʴ´ٸ� �ݵ�� nullptr�� �����)
	inline void SetKillCallBack(std::function<void()> _KillCallback)
	{
		KillCallback = _KillCallback;
	}

	//Enemy ���̱�
	void KillEnemy(std::shared_ptr<FieldEnemyBase> _Enemy);

	
	//Enemy�� ��ġ ����ϱ�
	void MarkGridPos(std::shared_ptr<FieldEnemyBase> _Enemy, const std::pair<int,int>& _Pos);


	//_Enemy�� �̵��Ϸ��� ��ġ�� _NextPos�� �ٸ� Enemy�� �����ϴ��� Ȯ���ϴ� �Լ�
	bool IsOtherStay(
		std::shared_ptr<FieldEnemyBase> _Enemy,
		const std::pair<int, int>& _NextPos,
		int _CheckArea = 0);

	

	//�ش� �������� ���͸� �ֱ������� ������ �� ȣ��
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

	//(Ȥ�ó� ���߿� ���� ����� FleldLevelBase::LevelChangeEnd���� �� �Լ��� ȣ���Ű�� ����)
	//���� �ڷᱸ���� û���Ѵ�
	void ClearDeathEnemy();

protected:

private:
	struct EnemyDataBlock
	{
		std::shared_ptr<FieldEnemyBase> EnemyPtr = nullptr;
		bool IsDeath = false;
		std::pair<int, int> GridPos;
		EnemyType Type;
	};

	std::vector<EnemyDataBlock> Enemies;
	FieldLevelBase* Level = nullptr;

	
	size_t KillCount = 0;
	std::function<void()> AllKillCallback = nullptr;
	std::function<void()> KillCallback = nullptr;

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

	//���� ��ġ ����뷻���� On/Off ó��
	void Update_DebugRender();
};

