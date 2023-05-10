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

	////this�����͸� shared_ptr�� ��ȯ
	//template <typename PtrType>
	//std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	//{
	//	return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<FSMBase>::shared_from_this());
	//}


	//State��ü
	template <typename EnumType>
	void ChangeState(EnumType _Type)
	{
		ChangeState(static_cast<size_t>(_Type));
	}
	void ChangeState(size_t _NextIndex);


	//���� ���°��� enum���� ĳ�����ؼ� �����ֱ�
	template <typename EnumType>
	inline EnumType GetNowState() const
	{
		return static_cast<EnumType>(CurIndex);
	}


	//���� ������Ʈ�� Update �����ֱ�
	void Update(float _DeltaTime);
	//���� ������Ʈ�� Render �����ֱ�
	void Render(float _DeltaTime);

	inline float GetFsmTime() const
	{
		return FsmTimer;
	}

protected:
	//�� FSM�� ���� State���� ���� ũ�� ����
	template <typename EnumType>
	void ResizeStates(EnumType _Count)
	{
		ResizeStates(static_cast<size_t>(_Count));
	}
	inline void ResizeStates(size_t _Size)
	{
		AllState.resize(_Size);
	}


	//�ڽĿ��� ���� State�� ������ֱ�
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

	//������� State�� �⺻ �ʱ�ȭ(�ȿ��� AllState�� ���)
	void InitState(std::shared_ptr<StateBase> _State, size_t _Index);
};

