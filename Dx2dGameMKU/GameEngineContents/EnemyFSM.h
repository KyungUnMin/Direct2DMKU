#pragma once
#include "FSMBase.h"


/*
	Enemy의 FSM은  각각의 Enemy가 직접 만들어주기로 했어
하지만 Enemy마다 고유의 스킬도 다를꺼야
이를 반영하기 위해 CreateState를 하면 반환값으로 해당 State를 돌려주게 했어
그러면 EnemyState는 functional를 사용해서 별도로 처리할수 있게끔 할까?

만약 이렇게 하면 Enemy쪽 클래스가 너무 비대해지지 않을까?

그리고 이렇게하면 ChangeState는 어떻게 처리해?
Enemy들 마다 별도의 enum class가 존재할텐데

<방법>
1. EnemyFSM에서 모든 Enemy들의 State를 갖고 있는다
	모두가 공통된 enum class를 사용하는것
	(하지만 이러면 배열의 빈 공간들이 생길것 -> 그나마 양호)

2. Enemy를 위한 맵으로 만든 FSM을 만든다?
	공통된 enum class에서 사용할 애들만 사용
	(차라리 배열의 빈 공간을 그냥 두는게 낫지 않아?)

3. 

--------


일단 공통된 State를 재활용하려면 enum class는 모두 공유하는게 맞을거 같다
또한 각각의 Enemy마다 특징이 있기 때문에 functional도 사용해야 할 것 같다
	(Enemy마다 일일히 다 FSM을 만들어 줄 수는 없어)
또한 Enemy 쪽에서 직접 사용할 State들을 지정해주도록 하자

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

	//어차피 FSM이 Enemy의 값 형태로 있기 때문에 shared 사용X
	FieldEnemyBase* Enemy = nullptr;
	
};

