#include "PrecompileHeader.h"
#include "FSMBase.h"
#include "StateBase.h"


FSMBase::FSMBase()
{
}

FSMBase::~FSMBase()
{
	AllState.clear();
}



void FSMBase::InitState(std::shared_ptr<StateBase> _State, size_t _Index)
{
	if (AllState.size() <= _Index)
	{
		MsgAssert("�������ַ��� State�� ������ ������ �Ѿ���ϴ�.\n ResizeStates�Լ��� ȣ�����־�� �մϴ�");
		return;
	}

	if (nullptr != AllState[_Index])
	{
		MsgAssert("�ش� ��ġ���� �̹� �ٸ� State�� �����մϴ�\n enum���� Ȯ���غ�����");
		return;
	}

	_State->FsmPtr = this;
	_State->Start();
	AllState[_Index] = _State;
}



void FSMBase::Update(float _DeltaTime)
{
	if (AllState.size() <= CurIndex)
	{
		MsgAssert("���� FSM�� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	AllState[CurIndex]->Update(_DeltaTime);
}

void FSMBase::Render(float _DeltaTime)
{
	if (AllState.size() <= CurIndex)
	{
		MsgAssert("���� FSM�� ���¸� ���������� �ʾҽ��ϴ�");
		return;
	}

	AllState[CurIndex]->Render(_DeltaTime);
}




void FSMBase::ChangeState(size_t _NextIndex)
{
	//�ڽĿ��� Resize�� ������ ����
	if (AllState.size() <= _NextIndex)
	{
		MsgAssert("FSM�� ����� State�� ������ �Ѿ �����Ͽ����ϴ�");
		return;
	}

	//���� ���°� ã��
	std::shared_ptr<StateBase>  PrevState = nullptr;
	if (CurIndex < AllState.size())
	{
		PrevState = AllState[CurIndex];
	}

	//���� ���°� ã��
	std::shared_ptr<StateBase>  NextState = AllState[_NextIndex];
	if (nullptr == NextState)
	{
		MsgAssert("�ٲٷ��� ��Ʋ State�� ������� ���� �����ϴ�");
		return;
	}

	//���� ���°� ��ü
	CurIndex = _NextIndex;

	//���� ���°��� �����ߴٸ� Exitȣ��
	if (nullptr != PrevState)
	{
		PrevState->ExitState();
	}

	//���� ���°��� Enterȣ��
	NextState->EnterState();
}
