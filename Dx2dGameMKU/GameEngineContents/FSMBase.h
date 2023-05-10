#pragma once

class StateBase;
class GameEngineActor;

class FSMBase : public std::enable_shared_from_this<FSMBase>
{
public:
	FSMBase();
	virtual ~FSMBase() = 0;

	FSMBase(const FSMBase& _Other) = delete;
	FSMBase(FSMBase&& _Other) noexcept = delete;
	FSMBase& operator=(const FSMBase& _Other) = delete;
	FSMBase& operator=(const FSMBase&& _Other) noexcept = delete;

	////this포인터를 shared_ptr로 변환
	//template <typename PtrType>
	//std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	//{
	//	return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<FSMBase>::shared_from_this());
	//}


	//State교체
	template <typename EnumType>
	void ChangeState(EnumType _Type)
	{
		ChangeState(static_cast<size_t>(_Type));
	}
	void ChangeState(size_t _NextIndex);


	//현재 상태값을 enum으로 캐스팅해서 돌려주기
	template <typename EnumType>
	inline EnumType GetNowState() const
	{
		return static_cast<EnumType>(CurIndex);
	}


	//현재 스테이트를 Update 돌려주기
	void Update(float _DeltaTime);
	//현재 스테이트를 Render 돌려주기
	void Render(float _DeltaTime);

	inline float GetFsmTime() const
	{
		return FsmTimer;
	}

protected:
	//이 FSM이 가질 State들의 벡터 크기 설정
	template <typename EnumType>
	void ResizeStates(EnumType _Count)
	{
		ResizeStates(static_cast<size_t>(_Count));
	}
	inline void ResizeStates(size_t _Size)
	{
		AllState.resize(_Size);
	}


	//자식에서 가질 State를 만들어주기
	template <typename StateType, typename EnumType>
	std::shared_ptr<StateBase> CreateState(EnumType _Index)
	{
		std::shared_ptr<StateBase> NewState = std::make_shared<StateType>();
		InitState(NewState, static_cast<size_t>(_Index));
		return NewState;
	}

	virtual void Test(){}


private:
	std::vector<std::shared_ptr<StateBase>> AllState;
	size_t CurIndex = 999999;

	float FsmTimer = 0.f;

	//만들어진 State를 기본 초기화(안에서 AllState에 등록)
	void InitState(std::shared_ptr<StateBase> _State, size_t _Index);
};

