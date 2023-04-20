#pragma once

class StateBase;
class GameEngineActor;

class FSMBase
{
public:
	FSMBase();
	virtual ~FSMBase() = 0;

	FSMBase(const FSMBase& _Other) = delete;
	FSMBase(FSMBase&& _Other) noexcept = delete;
	FSMBase& operator=(const FSMBase& _Other) = delete;
	FSMBase& operator=(const FSMBase&& _Other) noexcept = delete;

	//State��ü
	template <typename EnumType>
	void ChangeState(EnumType _Type)
	{
		ChangeState(static_cast<size_t>(_Type));
	}
	void ChangeState(size_t _NextIndex);


	//���� ���°��� enum���� ĳ�����ؼ� �����ֱ�
	template <typename EnumType>
	EnumType GetNowState()
	{
		return static_cast<EnumType>(CurIndex);
	}


	//���� ������Ʈ�� Update �����ֱ�
	void Update(float _DeltaTime);

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
	void CreateState(EnumType _Index)
	{
		std::shared_ptr<StateBase> NewState = std::make_shared<StateType>();
		InitState(NewState, static_cast<size_t>(_Index));
	}


private:
	std::vector<std::shared_ptr<StateBase>> AllState;
	size_t CurIndex = 999999;

	//������� State�� �⺻ �ʱ�ȭ(�ȿ��� AllState�� ���)
	void InitState(std::shared_ptr<StateBase> _State, size_t _Index);
};

