#pragma once
#include "FSMBase.h"


/*
	Enemy�� FSM��  ������ Enemy�� ���� ������ֱ�� �߾�
������ Enemy���� ������ ��ų�� �ٸ�����
�̸� �ݿ��ϱ� ���� CreateState�� �ϸ� ��ȯ������ �ش� State�� �����ְ� �߾�
�׷��� EnemyState�� functional�� ����ؼ� ������ ó���Ҽ� �ְԲ� �ұ�?

���� �̷��� �ϸ� Enemy�� Ŭ������ �ʹ� ��������� ������?

�׸��� �̷����ϸ� ChangeState�� ��� ó����?
Enemy�� ���� ������ enum class�� �������ٵ�

<���>
1. EnemyFSM���� ��� Enemy���� State�� ���� �ִ´�
	��ΰ� ����� enum class�� ����ϴ°�
	(������ �̷��� �迭�� �� �������� ����� -> �׳��� ��ȣ)

2. Enemy�� ���� ������ ���� FSM�� �����?
	����� enum class���� ����� �ֵ鸸 ���
	(���� �迭�� �� ������ �׳� �δ°� ���� �ʾ�?)

3. 

--------


�ϴ� ����� State�� ��Ȱ���Ϸ��� enum class�� ��� �����ϴ°� ������ ����
���� ������ Enemy���� Ư¡�� �ֱ� ������ functional�� ����ؾ� �� �� ����
	(Enemy���� ������ �� FSM�� ����� �� ���� ����)
���� Enemy �ʿ��� ���� ����� State���� �������ֵ��� ����

*/



enum class EnemyStateType
{
	Idle,
	Walk,

	COUNT
};

class FieldEnemyBase;

class EnemyFSM : public FSMBase
{
public:
	EnemyFSM();
	~EnemyFSM() override;

	EnemyFSM(const EnemyFSM& _Other) = delete;
	EnemyFSM(EnemyFSM&& _Other) noexcept = delete;
	EnemyFSM& operator=(const EnemyFSM& _Other) = delete;
	EnemyFSM& operator=(const EnemyFSM&& _Other) noexcept = delete;

	inline void Init(FieldEnemyBase* _Enemy)
	{
		Enemy = _Enemy;
	}

	template <typename StateType>
	std::shared_ptr<StateType> CreateState(EnemyStateType _State)
	{
		if (false == IsResized)
		{
			FSMBase::ResizeStates(EnemyStateType::COUNT);
			IsResized = true;
		}

		return std::dynamic_pointer_cast<StateType>(FSMBase::CreateState<StateType>(_State));
	}

	inline void ChangeState(EnemyStateType _NextState)
	{
		FSMBase::ChangeState(static_cast<size_t>(_NextState));
	}

protected:


private:
	bool IsResized = false;

	//������ FSM�� Enemy�� �� ���·� �ֱ� ������ shared ���X
	FieldEnemyBase* Enemy = nullptr;
	
};

