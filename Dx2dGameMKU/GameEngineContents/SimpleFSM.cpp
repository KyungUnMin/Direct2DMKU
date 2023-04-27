#include "PrecompileHeader.h"
#include "SimpleFSM.h"

SimpleFSM::SimpleFSM()
{

}

SimpleFSM::~SimpleFSM()
{

}

void SimpleFSM::AddState(size_t _Index, const SimpleFSMState& _State)
{
	if (States.size() <= _Index)
	{
		MsgAssert("SimpleFSM �迭�� ������ �Ѿ ���� �����߽��ϴ�");
		return;
	}
	
	if (true == States[_Index].Registered)
	{
		MsgAssert("�ش� ��ġ���� �ٸ� State�� �̹� �����մϴ�\nIndex : " + GameEngineString::ToString(static_cast<int>(_Index)));
		return;
	}
	
	States[_Index] = _State;
	States[_Index].Registered = true;
}


void SimpleFSM::ChangeState(size_t _Index)
{
	size_t PrevState = CurState;
	size_t NextState = _Index;
	CurState = _Index;
	StateLiveTime = 0.f;

	if (States.size() <= NextState)
	{
		MsgAssert("SimpleFSM �迭�� ������ �Ѿ ���� �����߽��ϴ�");
		return;
	}

	if (false == States[NextState].Registered)
	{
		MsgAssert("�ش� ��ġ���� State�� ��������� �ʾҽ��ϴ�\nIndex : " + GameEngineString::ToString(static_cast<int>(_Index)));
		return;
	}

	//ù ���� ��ȯ�� �ƴ� ��쿡��(�迭�� �ε��� ���� ������)
	if ((UINT32_MAX != PrevState) && (nullptr != States[PrevState].ExitCallBack))
	{
		States[PrevState].ExitCallBack();
	}


	if (nullptr != States[NextState].EnterCallBack)
	{
		States[PrevState].EnterCallBack();
	}
}



void SimpleFSM::Update(float _DeltaTime)
{
	if (UINT32_MAX == CurState)
	{
		MsgAssert("SimpleFSM�� ������ ù State�� ���������� �ʾҽ��ϴ�");
		return;
	}

	if (nullptr == States[CurState].UpdateCallBack)
		return;

	StateLiveTime += _DeltaTime;
	States[CurState].UpdateCallBack(_DeltaTime);
}
