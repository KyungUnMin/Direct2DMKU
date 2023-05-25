#pragma once

/*
Enemy�� ����/�Ҹ��� �������ش�
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

	//���ø��� ��������� ��ȯ���� ������ Enum���� ���� �޴´�
	std::shared_ptr<FieldEnemyBase> CreateEnemy(EnemyType _Type,const float4& _CreatePos);


	inline void SetAllKillCallback(std::function<void()> _Callback)
	{
		Callback = _Callback;
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

