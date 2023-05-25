#pragma once

/*
Enemy의 생성/소멸을 관리해준다
*/

class FieldLevelBase;
class FieldEnemyBase;

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

	//템플릿을 쓰고싶지만 순환참조 때문에 Enum으로 인자 받는다
	std::shared_ptr<FieldEnemyBase> CreateEnemy(EnemyType _Type,const float4& _CreatePos);


	inline void SetAllKillCallback(std::function<void()> _Callback)
	{
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

	bool CheckValidIndex(std::shared_ptr<FieldEnemyBase> _Enemy);
};

