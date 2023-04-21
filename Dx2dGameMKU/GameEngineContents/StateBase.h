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
	virtual void EnterState() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void ExitState() {}

private:
	FSMBase* FsmPtr = nullptr;
	
};

