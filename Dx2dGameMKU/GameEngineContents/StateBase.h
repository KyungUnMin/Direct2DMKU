#pragma once

class FSMBase;
class GameEngineActor;
class GameEngineLevel;

class StateBase
{
	friend FSMBase;

public:
	StateBase();
	virtual ~StateBase()= 0;

	StateBase(const StateBase& _Other) = delete;
	StateBase(StateBase&& _Other) noexcept = delete;
	StateBase& operator=(const StateBase& _Other) = delete;
	StateBase& operator=(const StateBase&& _Other) noexcept = delete;

protected:
	template <typename FSMTypePtr>
	FSMTypePtr* GetConvertFSM() const
	{
		return dynamic_cast<FSMTypePtr*>(FsmPtr);
	}

	inline FSMBase* GetFSM() const
	{
		return FsmPtr;
	}


	virtual void Start(){}
	virtual void EnterState();
	virtual void Update(float _DeltaTime);
	virtual void Render(float _DeltaTime) {}
	virtual void ExitState() {}

	inline float GetLiveTime() const
	{
		return Timer;
	}

	inline void ResetLiveTime()
	{
		Timer = 0.f;
	}

private:
	/*
		FSM들은 내부에서 값 형으로 들고 있을 예정이기 때문에
		동적할당이 안 일어난다. 그래서 스마트포인터가 아닌
		일반 포인터들을 이용
	*/
	FSMBase* FsmPtr = nullptr;

	float Timer = 0.f;
};

