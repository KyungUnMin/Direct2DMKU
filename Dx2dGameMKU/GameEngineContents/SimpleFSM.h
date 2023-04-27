#pragma once
#include <functional>

class SimpleFSMState
{
	friend class SimpleFSM;

public:
	std::function<void()> EnterCallBack= nullptr;
	std::function<void(float)> UpdateCallBack = nullptr;
	std::function<void()> ExitCallBack = nullptr;

	SimpleFSMState()
	{

	}

	SimpleFSMState(
		std::function<void()> _Enter,
		std::function<void(float)> _Update,
		std::function<void()> _Exit)
		: EnterCallBack(_Enter)
		, UpdateCallBack(_Update)
		, ExitCallBack(_Exit)
	{
	}

	SimpleFSMState(std::function<void(float)> _Update)
		:UpdateCallBack(_Update)
	{
	}

private:
	bool Registered = false;
};


class SimpleFSM
{
public:
	SimpleFSM();
	~SimpleFSM();

	SimpleFSM(const SimpleFSM& _Other) = delete;
	SimpleFSM(SimpleFSM&& _Other) noexcept = delete;
	SimpleFSM& operator=(const SimpleFSM& _Other) = delete;
	SimpleFSM& operator=(const SimpleFSM&& _Other) noexcept = delete;

	template <typename EnumValue>
	inline void Resize(EnumValue _Size)
	{
		Resize(static_cast<size_t>(_Size));
	}
	inline void Resize(size_t _Size)
	{
		States.resize(_Size);
	}


	template <typename EnumValue>
	inline void AddState(EnumValue _Index, const SimpleFSMState& _State)
	{
		AddState(static_cast<size_t>(_Index), _State);
	}
	void AddState(size_t _Index, const SimpleFSMState& _State);


	template <typename EnumValue>
	inline void ChangeState(EnumValue _Index)
	{
		ChangeState(static_cast<size_t>(_Index));
	}
	void ChangeState(size_t _Index);

	void Update(float _DeltaTime);

	inline float GetStateLiveTime() const
	{
		return StateLiveTime;
	}

protected:

private:
	std::vector<SimpleFSMState> States;
	size_t CurState = UINT32_MAX;
	float StateLiveTime = 0.f;
};

